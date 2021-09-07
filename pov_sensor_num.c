#include <avr/io.h> // this contains all the IO port definitions
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define TIMER1_PRESCALE_1 1
#define TIMER1_PRESCALE_8 2
#define TIMER1_PRESCALE_64 3
#define TIMER1_PRESCALE_256 4
#define TIMER1_PRESCALE_1024 5

// store all the image data in program memory (ROM)
// instead of RAM (the default)
static const uint8_t const large_image[] PROGMEM = {
	// ' ':
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	// '0':
	0b01111110,
	0b10100001,
	0b10011001,
	0b10000101,
	0b01111110,
	0b00000000,
	// '1':
	0b00000000,
	0b10000010,
	0b11111111,
	0b10000000,
	0b00000000,
	0b00000000,
	// '2':
	0b10000010,
	0b11000001,
	0b10100001,
	0b10010001,
	0b10001110,
	0b00000000,
	// '3':
	0b01000010,
	0b10000001,
	0b10001001,
	0b10001001,
	0b01110110,
	0b00000000,
	// '4':
	0b00011000,
	0b00010100,
	0b00010010,
	0b11111111,
	0b00010000,
	0b00000000,
	// '5':
	0b01001111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110001,
	0b00000000,
	// '6':
	0b01111110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110010,
	0b00000000,
	// '7':
	0b00000001,
	0b11000001,
	0b00110001,
	0b00001101,
	0b00000011,
	0b00000000,
	// '8':
	0b01110110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110110,
	0b00000000,
	// '9':
	0b01000110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01111110,
	0b00000000,
};

#define charsize 6 // number of rows of a char in the font
#define imagesize 7*charsize // number of digits we want to print

uint16_t EEMEM counter_calc = 0xaabb;
static volatile uint8_t imageindex = imagesize;
static volatile uint16_t number;

// this function is called when timer1 compare matches OCR1A
SIGNAL( TIMER1_COMPA_vect ) {
	if (imageindex < imagesize) {
		uint16_t no = number; // a copy of the number to display
		uint8_t chari = imageindex / charsize; // index of the char in the string
		uint8_t charc = imageindex % charsize; // index of the line in the char
		uint8_t charl = 0; // position of that char in the font large_image
		uint8_t i;
		for (i=0;i<5;i++) {
			if ((5-i) == chari) {
				charl = charsize * (no % 10 + 1); // position of that char in the font large_image (first is space)
			}
			no /= 10;
		}
		// read the image data from ROM
		PORTB = pgm_read_byte(large_image + charl + charc);
		imageindex++;
	}
	else {
		PORTB = 0;
	}
}

int main(void) {
	uint16_t no = 0;

	DDRB = 0xFF; // set all 8 pins on port B to outputs
	PORTB = 0; // set all pins off

	DDRD = 0xFB; // one input on pin D2
	PORTD = 0x04; // turn on pullup on pin D2

	TCCR1B = (1 << WGM12) | TIMER1_PRESCALE_1;
	OCR1A = (uint16_t)20000;
	TIMSK |= 1 << OCIE1A; // Output Compare Interrupt Enable (timer 1, OCR1A)
	sei(); // Set Enable Interrupts

	while (1) {
		no = 0;
#		define DELAY 5
#	if 1 // use debounce?
#		define BOUNCE 6
		int bounce_counter = BOUNCE;
		while (bounce_counter > BOUNCE / 3) {
			if (PIND & 0x4) {
				if (bounce_counter < BOUNCE)
					bounce_counter++;
			}
			else {
				if (bounce_counter > 0)
					bounce_counter--;
			}
#	else
		while (PIND & 0x4) { //}
#	endif
			_delay_ms(DELAY);
			no++;
		}
		_delay_ms(DELAY);
		no++;
		while (!(PIND & 0x4)) {
			_delay_ms(DELAY);
			no++;
		}
		_delay_ms(100);
		//number = no;
		number = eeprom_read_word(&counter_calc);
		imageindex = 0;
	}
}
