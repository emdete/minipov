#include <avr/io.h> // this contains all the IO port definitions
#include <avr/interrupt.h> // definitions for interrupts
#include <avr/sleep.h> // definitions for power-down modes
#include <avr/pgmspace.h> // definitions or keeping constants in program memory


// This function delays the specified number of 1/10 milliseconds
void delay_one_tenth_ms(unsigned long int ms) {
	unsigned long int timer;
	const unsigned long int DelayCount=87; // this value was determined by trial and error
	while (ms != 0) {
		// Toggling PD6 is done here to force the compiler to do this loop, rather than optimize it away
		for (timer=0; timer <= DelayCount; timer++) {
			PIND |= 0b01000000;
		}
		ms--;
	}
}

int main(void) {
	DDRB = 0xFF; // set all PortB pins as outputs
	DDRD = 0x7F; // set all PortD pins as outputs
	PORTB = 0b00000000; // all PORTB output pins Off
	PORTD = 0b00000111; // PORTD3 output pin Off, PORTD2 and PORTD1 and PORTD0 on (grounds)

	;

	MCUCR |= 0b00100000; // SE=1 (bit 5)
	MCUCR |= 0b00010000; // SM1:0=01 to enable Power Down Sleep Mode (bits 6, 4)
	delay_one_tenth_ms(10000); // wait 1 second
	PORTB = 0x00; // turn off all PORTB outputs
	PORTD = 0x00; // turn off all PORTD outputs
	DDRB = 0x00; // make PORTB all inputs
	DDRD = 0x00; // make PORTD all inputs
	sleep_cpu(); // put CPU into Power Down Sleep Mode
}
