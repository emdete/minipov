#!/usr/bin/env make -f
.PHONY: all clean
TARGET=sensor

all:
	make TARGET=$(TARGET) -f ../avr.mk $@

run:
	make TARGET=$(TARGET) -f ../avr.mk eeprom-$(TARGET)

clean:
	make TARGET=$(TARGET) -f ../avr.mk $@

