/**
 * YF-21 flow sensor specifications
 *
 * 120 L/H - 16  Hz - 480 Pulses/L
 * 240 L/H - 32.5Hz - 487 Pulses/L
 * 360 L/H - 49.3Hz - 493 Pulses/L
 * 480 L/H - 65.5Hz - 491.25 
 * 600 L/H - 82  Hz - 492
 * 720 L/H - 90.2Hz - 451
#include "main.h" 

// -------- Global Variables --------- //

// -------- Functions --------- //

int main(void) {
  // -------- Inits --------- //
  
  // clock_prescale_set(clock_div_1);                 /* CPU Clock: 8 MHz */
  initUSART();
  printString("OK");

  // ------ Event loop ------ //
  while (1) {
  printString("OK");
	  _delay_us(1000000);
  printString("OK");
	  _delay_us(1000000);
  printString("OK");
	  _delay_us(1000000);
  printString("OK");
	  _delay_us(1000000);
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
