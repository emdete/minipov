#include <avr/io.h> // this contains all the IO port definitions
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "font_5x8.h"
#define countof(x) (sizeof(x) / sizeof(*(x)))

#define TIMER1_PRESCALE_1 1
#define TIMER1_PRESCALE_8 2
#define TIMER1_PRESCALE_64 3
#define TIMER1_PRESCALE_256 4
#define TIMER1_PRESCALE_1024 5

// wait delay
#define delay 5
// number of bounces ignored
#define bounce 4
// additional wait before starte
#define wait 6
// ram array for the current text
uint8_t text[17];
// size of a pattern for a text
#define patternsize ((sizeof(text)-1)*font_width)
// eeprom array of texts to display
uint8_t ee_text[][sizeof(text)] EEMEM = {
	"The sun shone,  ",
	"having no       ",
	"alternative, on ",
	"the nothing new.",
	};
// eeprom count of texts in the array
uint8_t ee_text_count EEMEM = countof(ee_text);
// current index into the pattern to display
uint8_t patternindex = patternsize;

// this function is called when timer1 compare matches OCR1A
SIGNAL( TIMER1_COMPA_vect ) {
	uint8_t pattern = 0;
	if (patternindex < patternsize) {
		const void const* p = font_pattern(text[patternindex / font_width], patternindex % font_width);
		//pgm_read_byte(text + patternindex / font_width);
		if (p) {
			pattern = pgm_read_byte(p);
		}
		patternindex++;
	}
	PORTB = pattern;
}

int main(void) {
	uint8_t text_index = 0;
	uint8_t text_repeat = 3;
	eeprom_read_block(text, (void*)ee_text[text_index], sizeof(text));

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
		cli(); // Clear Enable Interrupts
		// output pattern
		if (!text_repeat--) {
			text_index = (text_index+1) % eeprom_read_byte((void*)&ee_text_count);
			eeprom_read_block(text, (void*)ee_text[text_index], sizeof(text));
			text_repeat = 3;
		}
		patternindex = 0;
		sei(); // Set Enable Interrupts
	}
}
