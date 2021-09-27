#!/usr/bin/env make -f
.PHONY: all clean
TARGET=various

all:
	make TARGET=$(TARGET) -f ../avr.mk $@

run:
	make TARGET=$(TARGET) -f ../avr.mk eeprom-$(TARGET)

dbg:
	make -C .. $@

clean:
	make TARGET=$(TARGET) -f ../avr.mk $@

