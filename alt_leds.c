#include <avr/io.h> // this contains all the IO port definitions
#include <util/delay.h> // this contains _delay_ms definition

int main(void) {
	DDRB = 0xFF; // set all 8 pins on port B to outputs
	PORTB = 0x0; // set all pins on port B low (turn off LEDs)
	while (1) {
		PORTB = 0xAA; // turn on LEDs #2,4,6,8
		_delay_ms(1000); // delay half a second
		PORTB = 0x55; // turn on LEDs #1,3,5,7
		_delay_ms(1000); // delay half a second
	}
}
