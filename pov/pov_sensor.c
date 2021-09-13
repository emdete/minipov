#include <avr/io.h> // this contains all the IO port definitions
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define TIMER1_PRESCALE_1 1
#define TIMER1_PRESCALE_8 2
#define TIMER1_PRESCALE_64 3
#define TIMER1_PRESCALE_256 4
#define TIMER1_PRESCALE_1024 5

// store all the image data in program memory (ROM)
// instead of RAM (the default)
#include "../text.h"

#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)))
#define imagesize NUM_ELEM(large_image)

uint8_t imageindex = imagesize;

// this function is called when timer1 compare matches OCR1A
SIGNAL( TIMER1_COMPA_vect ) {
	if (imageindex < imagesize) {
		// read the image data from ROM
		PORTB = pgm_read_byte(large_image + imageindex);
		imageindex++;
	}
	else {
		PORTB = 0;
	}
}

int main(void) {
// wait delay
#	define delay 5
// number of bounces ignored
#	define bounce 5
// additional wait before starte
#	define wait 3

	DDRB = 0xFF; // set all 8 pins on port B to outputs
	PORTB = 0; // set all pins off

	DDRD = 0xFB; // one input on pin D2
	PORTD = 0x04; // turn on pullup on pin D2
	/*
		the frequency of the interrupt overflow is determined by the
		prescaler and overflow value.
		freq = clock_frequency / ( 2 * prescaler * overflow_val)
		where prescaler can be 1, 8, 64, 256, or 1024
		clock_freq is 8MHz
		and overflow_val is 16bit

		the overflow value is placed in OCR1A, the prescale is set in TCCR1B
		so for example:
		A good POV frequency is around 400Hz
		desired freq = 400Hz
		clock freq = 8MHz
		8MHz / (400Hz * 2) = 10000
		since 10000 is less than 655536 (largest 16 bit number)
		OCR1A = 10000 and the prescale is 1
	*/

	TCCR1B = (1 << WGM12) | TIMER1_PRESCALE_1;
	OCR1A = (uint16_t)10000;

	TIMSK |= 1 << OCIE1A; // Output Compare Interrupt Enable (timer 1, OCR1A)

	sei(); // Set Enable Interrupts

	// loop forever
	while (1) {
		// wait for pressed
		uint8_t bounce_counter = bounce;
		while (bounce_counter > 0) {
			if (PIND & 0x4) {
				if (bounce_counter < bounce)
					bounce_counter++;
			}
			else {
				if (bounce_counter > 0)
					bounce_counter--;
			}
			_delay_ms(delay);
		}
		// wait for not pressed
		bounce_counter = bounce;
		while (bounce_counter > 0) {
			if (!(PIND & 0x4)) {
				if (bounce_counter < bounce)
					bounce_counter++;
			}
			else {
				if (bounce_counter > 0)
					bounce_counter--;
			}
			_delay_ms(delay);
		}
		// add additional wait
		for (bounce_counter=0;bounce_counter<wait;bounce_counter++) {
			_delay_ms(delay);
		}
		// output image
		imageindex = 0;
	}
}
