// https://nerd-corner.com/arduino-timer-interrupts-how-to-program-arduino-registers/
// see attachInterrupt(digitalPinToInterrupt(2), ereignis, RISING);
// https://www.arduino.cc/reference/de/language/functions/external-interrupts/attachinterrupt/
// http://gammon.com.au/interrupts
// https://github.com/khoih-prog/TimerInterrupt

#include <avr/eeprom.h>

#include "font_5x8.h"
#define font_width font_5x8_width
#define font_pattern font_5x8_pattern

#include "timer.h"
volatile uint16_t counter_index;
volatile uint8_t pin;
#include "command.h"
#include "pattern.h"

Pattern command;
#define PLAIN 0
#define BASE 2
#if PLAIN
static volatile uint8_t * out;
#endif

static void debug_pins() {
	uint8_t last = -1;
	for (pin=0;pin<22;pin++) {
		uint8_t port = digitalPinToPort(pin);
		if (port != last) {
			volatile uint8_t * out = portOutputRegister(port);
			volatile uint8_t * reg = portModeRegister(port);
			Serial.print((int)reg);Serial.println("<reg");
			Serial.print((int)out);Serial.println("<out");
			last = port;
		}
	}
}

static void timerHandler(void) {
#	if PLAIN
		*out = 1<<pin;
#	else
		counter_index++;
		digitalWrite(BASE+pin, LOW);
		pin = (pin + 1) % 8;
		digitalWrite(BASE+pin, HIGH);
#	endif
}

void setup() {
	command.setSerial(&Serial);
	debug_pins();
	counter_index = 0;
#	if PLAIN
		// this code does not work because the 8 output pins are not on the same output byte
		uint8_t port = digitalPinToPort(BASE);
		volatile uint8_t * reg = portModeRegister(port);
		out = portOutputRegister(port);
		*reg = 0xFF; // set all 8 pins on port B to outputs
		*out = 0; // set all pins off
#	else
		for (pin=0;pin<8;pin++) {
			pinMode(BASE+pin, OUTPUT);
			digitalWrite(BASE+pin, LOW);
		}
#	endif
	pin = 0;
	ITimer1.init();
	if (ITimer1.attachInterruptInterval(100, timerHandler)) {
		Serial.println(F("\rITimer1 started\n> "));
	}
	else {
		Serial.println(F("Can't start ITimer1. Select another freq. or timer"));
	}
}

void loop() {
	while (1) {
		if (command.available()) {
			command.process();
		}
	}
}
// vim:path=/usr/lib/avr/include
