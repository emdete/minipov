#define PROGMEM
#include "font_5x8.h"
#include <stdio.h>

void print_letter(unsigned char out) {
	printf("// %c\n", out);
	const unsigned char* p = font + (
		(out>='0'&&out<='9')?(out-'0'):
		(out>='A'&&out<='Z')?(out-'A'+10):
		(out>='a'&&out<='z')?(out-'a'+36):
		(out==' ')?(62):
		(63)) * 5;
	int j;
	for (j=0;j<5;j++) {
		int i;
		putchar('0');
		putchar('b');
		for (i=0;i<8;i++) {
			putchar(*p&(1<<(7-i))?'1':'0');
		}
		putchar(',');
		putchar('\n');
		p++;
	}
	printf("0b00000000,\n");
}

int main(int argc, char *argv[]) {
	int argi;
	printf("const uint8_t const large_image[] PROGMEM = {\n");
	for (argi=1;argi<argc;argi++) {
		char* argp = argv[argi];
		while (*argp) {
			print_letter(*argp);
			argp++;
		}
		print_letter(' ');
	}
	printf("}\n");
}
