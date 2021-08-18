#include <stdio.h>
#include "font_sysv.h"
#include "pivot.h"
#define countof(x) (sizeof(x) / sizeof(*(x)))

int main() {
	int i, j, k;
	printf("const unsigned char font_pivot[][8] = {{\n");
	for (i=0;i<countof(font_sysv);i++) {
		for (k=0;k<8;k++) {
			printf("\t0b");
			for (j=0;j<7;j++) {
				printf("%c", font_sysv[i][6-j] & (1<<(7-k))?'1':'0');
			}
			printf(",\n");
		}
		printf("\t},{\n");
	}
	printf("0\n");
	printf("}};\n");
	return 0;
}
