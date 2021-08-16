#include <avr/io.h> // this contains all the IO port definitions
#include <util/delay.h>

int main(void) {
	int s = 0x01; // low LED
	DDRB = 0xFF; // set port B to output only
	PORTB = 0; // turn off all LEDs
	DDRD = 0xFB; // one input on pin D2
	PORTD = 0x04; // turn on pullup on pin D2
	PORTB = s; // set state
	while (1) {
		_delay_ms(200);
		if (PIND & 0x4) { // if the sensor switch is off...
			if (s > 0x01) {
				s >>= 1;
			}
		}
		else { // if the sensor switch is on...
			if (s < 0x80) {
				s <<= 1;
			}
		}
		PORTB = s; // set new state
	}
}

