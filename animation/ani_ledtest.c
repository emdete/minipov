#include <avr/io.h> // this contains all the IO port definitions
#include <util/delay.h> // this contains _delay_ms definition

int main(void) {
	unsigned int state = 1;
	unsigned int delay = 100;
	DDRB = 0xFF; // set port B to output only
	PORTB = state; // turn off all LEDs but the first
	while (1) { // forever
		while (state != 0x80) { // animate up
			state <<= 1;
			PORTB = state;
			_delay_ms(delay);
		}
		while (state != 0x01) { // animate down
			state >>= 1;
			PORTB = state;
			_delay_ms(delay);
		}
	}
}
