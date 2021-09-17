#include <stdio.h>

#define PROGMEM
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
#include "font_5x8.h"
#include "font_7x8.h"
#include "font_8x8.h"

#define font_width font_8x8_width
#define font_pattern font_8x8_pattern

int main(int argc, char *argv[]) {
	int argi;
	printf("const uint8_t const large_image[] PROGMEM = {\n");
	for (argi=1;argi<argc;argi++) {
		char* argp = argv[argi];
		while (*argp) {
			printf("\t// %c\n", *argp);
			for (int index=0;index<font_width;index++) {
				uint8_t const* p = font_pattern(*argp, index);
				printf("\t0b");
				if (p) {
					for (int i=0;i<8;i++) {
						printf("%c", (*p)&(1<<(7-i))?'1':'0');
					}
				}
				else {
					printf("00000000");
				}
				printf(",\n");
			}
			argp++;
		}
	}
	printf("};\n");
}
