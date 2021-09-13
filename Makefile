#!/usr/bin/env make -f
.PHONY: all clean
TARGET=pov_sensor_num

all:
	make TARGET=$(TARGET) -f avr.mk $@

clean:
	make TARGET=$(TARGET) -f avr.mk $@

dbg:
	$(foreach remote,$(shell git remote),$(shell git push $(remote)))

# generate text header
gen.h: gen_pov
	./gen_pov $(TEXT) | tee gen.h

# compile generator
gen_pov: gen_pov.c
	gcc -o $@ $<

