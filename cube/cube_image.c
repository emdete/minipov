/* LEDcube Firmware for use with ATtiny2313 25-December-09
Distributed under Creative Commons 3.0 -- Attib & Share Alike */

/* This firmware lights up the 3x3x3 LED cube matrix in the animation sequence given in imageTab The orientation is: with the serial-port connector facing to your right. */

/* to program the ATtiny2313, execute the following command: make program-ledcube
If the microcontroller has never been programmed before, the fuse bytes need to be programmed once: make burn-fuse */

#include <avr/io.h> // this contains all the IO port definitions
#include <avr/interrupt.h> // definitions for interrupts
#include <avr/sleep.h> // definitions for power-down modes
#include <avr/pgmspace.h> // definitions or keeping constants in program memory

/* The hardware for this project is as follows:
	ATtiny2313 has 20 pins:
Note: the orientation is: with the serial-port connector facing to your right.
	pin 1 connects to serial port programming circuitry
	pin 2 PD0 - ground for bottom plane of 3x3 LEDs
	pin 3 PD1 - ground for middle plane of 3x3 LEDs
	pin 6 PD2 - ground for top plane of 3x3 LEDs
	pin 7 PD3 - +V for back-left LED of each plane
	pin 10 ground
	pin 12 PB0 - +V for front-right LED of each plane
	pin 13 PB1 - +V for middle-right LED of each plane
	pin 14 PB2 - +V for front-middle LED of each plane
	pin 15 PB3 - +V for middle-middle LED of each plane
	pin 16 PB4 - +V for front-left LED of each plane
	pin 17 PB5 - +V for middle-left LED of each plane -- also connects to serial port programming circuitry
	pin 18 PB6 - +V for back-right LED of each plane -- also connects to serial port programming circuitry
	pin 19 PB7 - +V for back-middle LED of each plane -- also connects to serial port programming circuitry
	pin 20 +3v
All other pins are unused

This firmware requires that the clock frequency of the ATtiny
	is the default that it is shipped with: 8.0MHz internal oscillator */

/* The C compiler creates code that will transfer all constants into RAM when
 * the microcontroller
resets. Since this firmware has a table (imageTab) that is too large to
transfer into RAM, the C compiler needs to be told to keep it in program memory
space. This is accomplished by the macro PROGMEM (this is used, below, in the
definition for the imageTab). Since the C compiler assumes that constants are
in RAM, rather than in program memory, when accessing the imageTab, we need to
use the pgm_read_byte() and pgm_read_dword() macros, and we need to use the
imageTab as an address, i.e., precede it with "&". For example, to access
imageTab[3].TopFrontRow, which is a byte, this is how to do it:
	pgm_read_byte( &imageTab[3].TopFrontRow );
And to access imageTab[3].imageDuration, which is a double-word, this is how to do it:
	pgm_read_dword( &imageTab[3].imageDuration );
*/


// table of values for 3x3x3 LEDs
// 0 is off, 1 is on for each LED
// last element must have 0 duration
// all row variables only need 3 bits,
// but for simplicity of programming these each have 8-bit values in this firmware
struct imageElement {
	unsigned char TopFrontRow; // 3 bits: top-front-left, top-front-mid, top-front-right
	unsigned char TopMidRow; // 3 bits: top-mid-left, top-mid-mid, top-mid-right
	unsigned char TopBackRow; // 3-bits: top-back-left, top-back-mid, top-back-right
	unsigned char MidFrontRow; // 3-bits: mid-front-left, mid-front-mid, mid-front-right
	unsigned char MidMidRow; // 3 bits: mid-mid-left, mid-mid-mid, mid-mid-right
	unsigned char MidBackRow; // 3-bits: mid-back-left, mid-back-mid, mid-back-right
	unsigned char BotFrontRow; // 3-bits: bot-front-left, bot-front-mid, bot-front-right
	unsigned char BotMidRow; // 3 bits: bot-mid-left, bot-mid-mid, bot-mid-right
	unsigned char BotBackRow; // 3-bits: bot-back-left, bot-back-mid, bot-back-right
	unsigned long int imageDuration; // Duration for this element to be displayed before going to next element (divide by 10,000 to get seconds)
} const imageTab[] PROGMEM = {
	{ 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 20000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 30000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 40000 },

	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 50000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 50000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 50000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 50000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 40000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 40000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 40000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 40000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 30000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 30000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 30000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 30000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 20000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 10000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 7000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 4000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 4000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 4000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 4000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 7000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 10000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b101, 0b111, 0b111, 0b111, 0b111, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b100, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b110, 0b110, 0b000, 0b110, 0b110, 20000 },
	{ 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 0b111, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b111, 0b111, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 20000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 20000 },

	{ 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 20000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 20000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 10000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 10000 },
	{ 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 10000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 10000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 7000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 7000 },
	{ 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 7000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 7000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 7000 },
	{ 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 7000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 7000 },
	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 10000 },
	{ 0b000, 0b000, 0b000, 0b111, 0b111, 0b111, 0b000, 0b000, 0b000, 10000 },

	{ 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0 }, // this is a dummy element for end of table (duration=0)
};

// This function delays the specified number of 1/10 milliseconds
void delay_one_tenth_ms(unsigned long int ms) {
	unsigned long int timer;
	const unsigned long int DelayCount=87; // this value was determined by trial and error

	while (ms != 0) {
		// Toggling PD6 is done here to force the compiler to do this loop, rather than optimize it away
		for (timer=0; timer <= DelayCount; timer++) {PIND |= 0b01000000;};
		ms--;
	}
}


// This function displays a 3x3x3 image by multiplexing through the images for the 3 planes.
// The multiplex rate is about 111Hz.
// This function also acts as a delay for the Duration specified.
void displayImage(int index) {
	unsigned long int duration = pgm_read_dword( &imageTab[index].imageDuration );
	unsigned char tempA, tempB, tempC, tempD;
	for (int i=0; i<(duration/(90*3*2)); i++) {
		// first we will turn on all of the LEDs that imageTab says to turn on for the top plane (but only for 30msec)
		tempA = pgm_read_byte( &imageTab[index].TopFrontRow ); // we now have 3 bits: top-front-left, top-front-mid, top-front-right -- these go to PB4, PB2, PB0, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is top-front-right, which goes to PB0
		tempB = tempB & 0b010; // this is top-front-mid, which goes to PB2
		tempB = tempB << 1; // the bit is now in bit 2 (ready for PB2)
		tempC = tempC & 0b100; // this is top-front-left, which goes to PB4
		tempC = tempC << 2; // the bit is now in bit 4 (ready for PB4)
		tempD = tempA | tempB | tempC;
		tempA = pgm_read_byte( &imageTab[index].TopMidRow ); // we now have 3 bits: top-mid-left, top-mid-mid, top-mid-right -- these go to PB5, PB3, PB1, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is top-mid-right, which goes to PB1
		tempA = tempA << 1; // the bit is now in bit 1 (ready for PB1)
		tempB = tempB & 0b010; // this is top-mid-mid, which goes to PB3
		tempB = tempB << 2; // the bit is now in bit 3 (ready for PB3)
		tempC = tempC & 0b100; // this is top-mid-left, which goes to PB5
		tempC = tempC << 3; // the bit is now in bit 5 (ready for PB5)
		tempD = tempD | tempA | tempB | tempC;
		tempA = pgm_read_byte( &imageTab[index].TopBackRow ); // we now have 3 bits: top-back-left, top-back-mid, top-back-right -- these go to PD3, PB7, PB6, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is top-back-right, which goes to PB6
		tempA = tempA << 6; // the bit is now in bit 6 (ready for PB6)
		tempB = tempB & 0b010; // this is top-back-mid, which goes to PB7
		tempB = tempB << 6; // the bit is now in bit 7 (ready for PB7)
		tempC = tempC & 0b100; // this is top-back-left, which goes to PD3
		tempC = tempC << 1; // the bit is now in bit 3 (ready for PD3)
		tempD = tempD | tempA | tempB;
		PORTB |= tempD;
		PORTD |= tempC;
		PORTD &= ~(1<<PD2); // turn on top plane by making bit 2 of PORTD Low
		delay_one_tenth_ms(30);
		PORTD |= (1<<PD2); // turn off top plane by making bit 2 of PORTD High
		PORTB &= ~tempD;
		PORTD &= ~tempC;

		// now we will turn on all of the LEDs that imageTab says to turn on for the middle plane (but only for 30msec)
		tempA = pgm_read_byte( &imageTab[index].MidFrontRow ); // we now have 3 bits: mid-front-left, mid-front-mid, mid-front-right -- these go to PB4, PB2, PB0, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is mid-front-right, which goes to PB0
		tempB = tempB & 0b010; // this is mid-front-mid, which goes to PB2
		tempB = tempB << 1; // the bit is now in bit 2 (ready for PB2)
		tempC = tempC & 0b100; // this is mid-front-left, which goes to PB4
		tempC = tempC << 2; // the bit is now in bit 4 (ready for PB4)
		tempD = tempA | tempB | tempC;
		tempA = pgm_read_byte( &imageTab[index].MidMidRow ); // we now have 3 bits: mid-mid-left, mid-mid-mid, mid-mid-right -- these go to PB5, PB3, PB1, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is mid-mid-right, which goes to PB1
		tempA = tempA << 1; // the bit is now in bit 1 (ready for PB1)
		tempB = tempB & 0b010; // this is mid-mid-mid, which goes to PB3
		tempB = tempB << 2; // the bit is now in bit 3 (ready for PB3)
		tempC = tempC & 0b100; // this is mid-mid-left, which goes to PB5
		tempC = tempC << 3; // the bit is now in bit 5 (ready for PB5)
		tempD = tempD | tempA | tempB | tempC;
		tempA = pgm_read_byte( &imageTab[index].MidBackRow ); // we now have 3 bits: mid-back-left, mid-back-mid, mid-back-right -- these go to PD3, PB7, PB6, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is mid-back-right, which goes to PB6
		tempA = tempA << 6; // the bit is now in bit 6 (ready for PB6)
		tempB = tempB & 0b010; // this is mid-back-mid, which goes to PB7
		tempB = tempB << 6; // the bit is now in bit 7 (ready for PB7)
		tempC = tempC & 0b100; // this is mid-back-left, which goes to PD3
		tempC = tempC << 1; // the bit is now in bit 3 (ready for PD3)
		tempD = tempD | tempA | tempB;
		PORTB |= tempD;
		PORTD |= tempC;
		PORTD &= ~(1<<PD1); // turn on middle plane by making bit 1 of PORTD Low
		delay_one_tenth_ms(30);
		PORTD |= (1<<PD1); // turn off middle plane by making bit 1 of PORTD High
		PORTB &= ~tempD;
		PORTD &= ~tempC;

		// now we will turn on all of the LEDs that imageTab says to turn on for the bottom plane (but only for 30msec)
		tempA = pgm_read_byte( &imageTab[index].BotFrontRow ); // we now have 3 bits: bot-front-left, bot-front-mid, bot-front-right -- these go to PB4, PB2, PB0, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is bot-front-right, which goes to PB0
		tempB = tempB & 0b010; // this is bot-front-mid, which goes to PB2
		tempB = tempB << 1; // the bit is now in bit 2 (ready for PB2)
		tempC = tempC & 0b100; // this is bot-front-left, which goes to PB4
		tempC = tempC << 2; // the bit is now in bit 4 (ready for PB4)
		tempD = tempA | tempB | tempC;
		tempA = pgm_read_byte( &imageTab[index].BotMidRow ); // we now have 3 bits: bot-mid-left, bot-mid-mid, bot-mid-right -- these go to PB5, PB3, PB1, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is bot-mid-right, which goes to PB1
		tempA = tempA << 1; // the bit is now in bit 1 (ready for PB1)
		tempB = tempB & 0b010; // this is bot-mid-mid, which goes to PB3
		tempB = tempB << 2; // the bit is now in bit 3 (ready for PB3)
		tempC = tempC & 0b100; // this is bot-mid-left, which goes to PB5
		tempC = tempC << 3; // the bit is now in bit 5 (ready for PB5)
		tempD = tempD | tempA | tempB | tempC;
		tempA = pgm_read_byte( &imageTab[index].BotBackRow ); // we now have 3 bits: bot-back-left, bot-back-mid, bot-back-right -- these go to PD3, PB7, PB6, respectively
		tempB = tempA;
		tempC = tempA;
		tempA = tempA & 0b001; // this is bot-back-right, which goes to PB6
		tempA = tempA << 6; // the bit is now in bit 6 (ready for PB6)
		tempB = tempB & 0b010; // this is bot-back-mid, which goes to PB7
		tempB = tempB << 6; // the bit is now in bit 7 (ready for PB7)
		tempC = tempC & 0b100; // this is bot-back-left, which goes to PD3
		tempC = tempC << 1; // the bit is now in bit 3 (ready for PD3)
		tempD = tempD | tempA | tempB;
		PORTB |= tempD;
		PORTD |= tempC;
		PORTD &= ~(1<<PD0); // turn on bottom plane by making bit 0 of PORTD Low
		delay_one_tenth_ms(30);
		PORTD |= (1<<PD0); // turn off bottom plane by making bit 0 of PORTD High
		PORTB &= ~tempD;
		PORTD &= ~tempC;
	}
}


int main(void) {
	DDRB = 0xFF; // set all PortB pins as outputs
	DDRD = 0x7F; // set all PortD pins as outputs
	PORTB = 0x00; // all PORTB output pins Off
	PORTD = 0b00000111; // PORTD3 output pin Off, PORTD2 and PORTD1 and PORTD0 on (grounds)

	// loop through entier Image Table a bunch of times
	for (int count=0; count<30; count++) {
		// loop through entire Image Table of Image Elements
		// each Image Element consists of a 3 planes of 3x3 LED (each LED on or off) data and a Duration
		int i = 0;
		do {
			displayImage(i);
			i++;
		} while (pgm_read_byte(&imageTab[i].imageDuration) != 0); // 0 signifies end of table
	}

	// Shut down everything and put the CPU to sleep
	MCUCR |= 0b00100000; // SE=1 (bit 5)
	MCUCR |= 0b00010000; // SM1:0=01 to enable Power Down Sleep Mode (bits 6, 4)
	delay_one_tenth_ms(10000); // wait 1 second
	PORTB = 0x00; // turn off all PORTB outputs
	PORTD = 0x00; // turn off all PORTD outputs
	DDRB = 0x00; // make PORTB all inputs
	DDRD = 0x00; // make PORTD all inputs
	sleep_cpu(); // put CPU into Power Down Sleep Mode
}
