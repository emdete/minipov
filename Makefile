#!/usr/bin/env make -f
.PHONY: all clean

all: text.h

clean:
	$(foreach dir,$(dir $(wildcard */Makefile)),make -C $(dir) $@; )

dbg:
	$(foreach remote,$(shell git remote),$(shell git push $(remote)))

# generate text header
text.h: gen_pov
	./gen_pov $(TEXT) | tee text.h

# compile generator
gen_pov: gen_pov.c
	gcc -o $@ $<

