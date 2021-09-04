#include <stdio.h>
#define PROGMEM
#include "font_5x8.h"
#include "font_sysv.h"

int main(int argc, char *argv[]) {
	int argi;
	printf("const uint8_t const large_image[] PROGMEM = {\n");
	for (argi=1;argi<argc;argi++) {
		char* argp = argv[argi];
		while (*argp) {
			print_letter_5x8(*argp);
			argp++;
		}
		print_letter_5x8(' ');
	}
	printf("};\n");
}
