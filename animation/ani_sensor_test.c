#include <avr/io.h> // this contains all the IO port definitions
#include <util/delay.h>

static void wait_for_on(void);
static inline void wait_for_on(void) {
	while (PIND & 0x4) { // wait until the sensor switch is off...
		_delay_ms(1);
	}
}
static void wait_for_off(void);
static inline void wait_for_off(void) {
	while (!(PIND & 0x4)) { // wait until the sensor switch is off...
		_delay_ms(1);
	}
}

#define break_if_on() if (PIND & 0x4) break; else
#define break_if_off() if (!(PIND & 0x4)) break; else

int main(void) {
	int s = 0x0f; // low 4 LEDs
	DDRB = 0xFF; // set port B to output only
	PORTB = 0; // turn off all LEDs
	DDRD = 0xFB; // one input on pin D2
	PORTD = 0x04; // turn on pullup on pin D2
	while (1) {
		PORTB = s;
		wait_for_on();
		while (s != 0xf0) { // loop animation until high LEDs are on
			s <<= 1; // shift the LEDs
			_delay_ms(200); // wait a bit
			break_if_off();
			PORTB = s; // set new state
		}
		_delay_ms(1);
		s = 0x0f; // low 4 LEDs
	}
}
