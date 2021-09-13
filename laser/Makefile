#!/usr/bin/env make -f
.PHONY: all dbg clean
TARGET=pov_sensor_num

all:
	make TARGET=$(TARGET) -f ../avr.mk $@

dbg:
	make -C .. $@

clean:
	make TARGET=$(TARGET) -f ../avr.mk $@

