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
#include "main.h" 

// -------- Global Variables --------- //

// -------- Functions --------- //

static inline void initTimer() {
	TCCR1B |= (1 << WGM12);
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << CS01 | 1 << CS00);
	OCR1A = 60000;
}

int x;
int pulse_count = 0;
ISR(TIMER1_COMPA_vect) {
	if (x > 5) {
		printWord(pulse_count);
		x = 0;
	}
	x = x+1;
}

ISR(INT1_vect) {
	pulse_count += 1;
}

void initPinInterrupt() {
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
  initTimer();
  initPinInterrupt();

  // ------ Event loop ------ //
  sei();
  while (1) {
	  printWord(pulse_count);
	  _delay_ms(2000);
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
