#include <avr/io.h> // this contains all the IO port definitions
#include <util/delay.h>

void delay_ms( uint16_t milliseconds)
{
	for( ; milliseconds > 0; milliseconds--)
	{
		_delay_ms( 1);
	}
}


int main(void) {

	DDRB = 0xFF; // set port B to output only
	PORTB = 0; // turn off all LEDs

	DDRD = 0xFB; // one input on pin D2
	PORTD = 0x04; // turn on pullup on pin D2

	while (1) {
		if (PIND & 0x4) { // if the sensor switch is off...
			PORTB = 0xf0;
		}
		else { // if the sensor switch is on...
			int s = 0x0f;
			PORTB = s;
			while (s != 0xf0) {
				s <<= 1;
				delay_ms(100);
				PORTB = s;
			}
		}
	}
}
