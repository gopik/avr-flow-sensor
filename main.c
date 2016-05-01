#include "main.h" 

/**
 * YF-21 flow sensor specifications
 *
 * 120 L/H - 16  Hz - 480 Pulses/L
 * 240 L/H - 32.5Hz - 487 Pulses/L
 * 360 L/H - 49.3Hz - 493 Pulses/L
 * 480 L/H - 65.5Hz - 491.25 
 * 600 L/H - 82  Hz - 492
 * 720 L/H - 90.2Hz - 451
 **/

// -------- Global Variables --------- //

int timer0_overflow_count;
int pulse_count = 0;
int total_pulse_count = 0;
int num_seconds = 0;
volatile int liters;

// -------- Functions --------- //

static inline void init_timer() {
	TCCR0 |= (1 << CS00);
	TIMSK |= (1 << TOIE0); // Enable interrupt on TIMER0 overflow
}

static void per_second_callback() {
	liters += (pulse_count/450);
	pulse_count %= 450;
}

static void initExternalInterrupt() {
	DDRD &= ~(1 << DD2);     // Clear the PD2 pin
	// PD2 (INT0 pin) is now an input
	PORTD |= (1 << PIN2);    // turn On the Pull-up
	// PD0 is now an input with pull-up enabled
	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC00 | 1 << ISC01);
}

// -------- ISRs --------------------//

ISR(TIMER0_OVF_vect) {
	// On 8 MHz clock, 1 sec = 31250 * 256 => 31250 overflows of timer0
	timer0_overflow_count += 1;
	if (timer0_overflow_count == 31250) {
		timer0_overflow_count = 0;
		per_second_callback();
	}
}

ISR(INT0_vect) {
	pulse_count += 1;
	total_pulse_count += 1;
}

// ------------- Main Loop ------------//

int main(void) {
  // -------- Inits --------- //
  
  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */
  initUSART();
  init_timer();
  initExternalInterrupt();

  // ------ Event loop ------ //
  sei();
  int poll_liters = liters;
  while (1) {
	  printWord(poll_liters);
	  if (liters > poll_liters) {
		  poll_liters = liters;
		  printString("L");
		  printWord(poll_liters);
	  }
	  printString("TP");
	  printWord(total_pulse_count);
	  printString("TS");
	  printWord(num_seconds);
	  _delay_ms(1000);
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
