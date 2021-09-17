#!/usr/bin/env make -f
.PHONY: all dbg clean
TEXT="Free Software"

# generate text header
all: gen_pov

	./gen_pov $(TEXT) | tee text.h |sed 's/0b//'| tr 0,1 \ \ X

run: test
	./test

test: test.c

clean:
	$(foreach dir,$(dir $(wildcard */Makefile)),make -C $(dir) $@; )

dbg:
	$(foreach remote,$(shell git remote),$(shell git push $(remote)))

# compile generator
gen_pov: gen_pov.c Makefile font_*.h
	gcc -o $@ $<

