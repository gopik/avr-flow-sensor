/**
 * YF-21 flow sensor specifications
 *
 * 120 L/H - 16  Hz - 480 Pulses/L
 * 240 L/H - 32.5Hz - 487 Pulses/L
 * 360 L/H - 49.3Hz - 493 Pulses/L
 * 480 L/H - 65.5Hz - 491.25 
 * 600 L/H - 82  Hz - 492
 * 720 L/H - 90.2Hz - 451
 * p pulses => (62*p^2 + 15*p + 95756)*10^-7 liters
 **/
#include "main.h" 

// -------- Global Variables --------- //

int timer0_overflow_count;
int pulse_count = 0;
// -------- Functions --------- //

void per_second_callback();

static inline void init_timer() {
	TIMSK |= (1 << TOIE0); // Enable interrupt on TIMER0 overflow
}

ISR(TIMER0_OVF_vect) {
	// On 8 MHz clock, 1 sec = 31250 * 256 => 31250 overflows of timer0
	timer0_overflow_count += 1;
	if (timer0_overflow_count == 31250) {
		timer0_overflow_count = 0;
		per_second_callback();
	}
}

int liters;
int tmp_hi_precision_count;

void per_second_callback() {
	int frequency = pulse_count;
	pulse_count = 0;
	tmp_hi_precision_count += 62*frequency*frequency + 15*frequency + 95756;
	liters += (tmp_hi_precision_count / 10000000);
	tmp_hi_precision_count %= 10000000;
}

ISR(INT1_vect) {
	pulse_count += 1;
}

void initExternalInterrupt() {
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	    // PD2 (INT0 pin) is now an input
	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	//         // PD0 is now an input with pull-up enabled
	GICR |= (1 << INT1);
	MCUCR |= (1 << ISC11);
}

int main(void) {
  // -------- Inits --------- //
  
  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */
  initUSART();
  init_timer();
  initExternalInterrupt();

  // ------ Event loop ------ //
  sei();
  while (1) {
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
