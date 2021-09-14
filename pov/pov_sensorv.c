#include <avr/io.h> // this contains all the IO port definitions
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#define countof(x) (sizeof (x) / sizeof (*(x)))

#define TIMER1_PRESCALE_1 1
#define TIMER1_PRESCALE_8 2
#define TIMER1_PRESCALE_64 3
#define TIMER1_PRESCALE_256 4
#define TIMER1_PRESCALE_1024 5

static const uint8_t const font_5x8[] PROGMEM = {
	0b01111110,
	0b10100001,
	0b10011001,
	0b10000101,
	0b01111110, //0

	0b00000000,
	0b10000010,
	0b11111111,
	0b10000000,
	0b00000000, //1

	0b10000010,
	0b11000001,
	0b10100001,
	0b10010001,
	0b10001110, //2

	0b01000010,
	0b10000001,
	0b10001001,
	0b10001001,
	0b01110110, //3

	0b00011000,
	0b00010100,
	0b00010010,
	0b11111111,
	0b00010000, //4

	0b01001111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110001, //5

	0b01111110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110010, //6

	0b00000001,
	0b11000001,
	0b00110001,
	0b00001101,
	0b00000011, //7

	0b01110110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110110, //8

	0b01000110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01111110, //9

	0b11111110,
	0b00001001,
	0b00001001,
	0b00001001,
	0b11111110, //A

	0b11111111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110110, //B

	0b01111110,
	0b10000001,
	0b10000001,
	0b10000001,
	0b01000010, //C

	0b11111111,
	0b10000001,
	0b10000001,
	0b10000001,
	0b01111110, //D

	0b11111111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b10000001, //E

	0b11111111,
	0b00001001,
	0b00001001,
	0b00001001,
	0b00000001, //F

	0b01111110,
	0b10000001,
	0b10000001,
	0b10010001,
	0b11110010, //G

	0b11111111,
	0b00001000,
	0b00001000,
	0b00001000,
	0b11111111, //H

	0b00000000,
	0b10000001,
	0b11111111,
	0b10000001,
	0b00000000, //I

	0b01100000,
	0b10000000,
	0b10000001,
	0b01111111,
	0b00000000, //J

	0b11111111,
	0b00001000,
	0b00010100,
	0b00100010,
	0b11000001, //K

	0b11111111,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000, //L

	0b11111111,
	0b00000110,
	0b00111000,
	0b00000110,
	0b11111111, //M

	0b11111111,
	0b00000110,
	0b00011000,
	0b01100000,
	0b11111111, //N

	0b01111110,
	0b10000001,
	0b10000001,
	0b10000001,
	0b01111110, //O

	0b11111111,
	0b00001001,
	0b00001001,
	0b00001001,
	0b00000110, //P

	0b01111110,
	0b10000001,
	0b10100001,
	0b01000001,
	0b10111110, //Q

	0b11111111,
	0b00001001,
	0b00001001,
	0b00011001,
	0b11100110, //R

	0b01000110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110010, //S

	0b00000001,
	0b00000001,
	0b11111111,
	0b00000001,
	0b00000001, //T

	0b01111111,
	0b10000000,
	0b10000000,
	0b10000000,
	0b01111111, //U

	0b00011111,
	0b01100000,
	0b10000000,
	0b01100000,
	0b00011111, //V

	0b11111111,
	0b01100000,
	0b00011100,
	0b01100000,
	0b11111111, //W

	0b11000011,
	0b00110100,
	0b00001000,
	0b00110100,
	0b11000011, //X

	0b00000011,
	0b00001100,
	0b11110000,
	0b00001100,
	0b00000011, //Y

	0b11000001,
	0b10100001,
	0b10011001,
	0b10000101,
	0b10000011, //Z

	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000, //blank

	0b11111111,
	0b10000001,
	0b10000001,
	0b10000001,
	0b11111111, //unknown
	};
#define font_width 5
#define font_widthw (font_width+1)
static uint8_t text[17] = "BELPHEGOR       ";
uint8_t ee_text[][17] EEMEM = {
	"FREE SOFTWARE   ",
	};
#define patternsize ((sizeof(text)-1)*font_widthw)
static uint8_t patternindex = patternsize;

// this function is called when timer1 compare matches OCR1A
SIGNAL( TIMER1_COMPA_vect ) {
	if (patternindex < patternsize) {
		if (patternindex % font_widthw < font_width) {
			// font is 0-9 A-Z
			//uint8_t c = pgm_read_byte(text + patternindex / font_widthw);
			uint8_t c = text[patternindex / font_widthw];
			uint16_t patterni = 0;
			if (c>='0' && c<='9') {
				patterni += c - '0';
			}
			else {
				patterni += 10;
				if (c>='A' && c<='Z') {
					patterni += c - 'A';
				}
				else if (c>='a' && c<='z') {
					patterni += c - 'a';
				}
				else {
					patterni += 26;
					if (c==' ') {
						;
					}
					else {
						patterni++;
					}
				}
			}
			patterni *= font_width;
			patterni += patternindex % font_widthw;
			PORTB = pgm_read_byte(font_5x8 + patterni);
		}
		else {
			PORTB = 0b00000000;
		}
		patternindex++;
	}
	else {
		PORTB = 0;
	}
}

int main(void) {
	eeprom_read_block(text, ee_text[0], sizeof(text));
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
		// output pattern
		patternindex = 0;
	}
}
