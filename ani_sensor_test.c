#include <avr/io.h> // this contains all the IO port definitions
#include <util/delay.h>

int main(void) {
	DDRB = 0xFF; // set port B to output only
	PORTB = 0; // turn off all LEDs
	DDRD = 0xFB; // one input on pin D2
	PORTD = 0x04; // turn on pullup on pin D2
	while (1) {
		if (PIND & 0x4) { // if the sensor switch is off...
			PORTB = 0xf0; // high 4 LEDs on
		}
		else { // if the sensor switch is on...
			int s = 0x0f; // low 4 LEDs
			PORTB = s;
			while (!(PIND & 0x4)) { // wait until the sensor switch is off...
				_delay_ms(1);
			}
			while (s != 0xf0) { // loop animation until high LEDs are on
				s <<= 1; // shift the LEDs
				_delay_ms(200); // wait a bit
				PORTB = s; // set new state
			}
		}
		_delay_ms(1);
	}
}
