
static const uint8_t const font_5x8[] PROGMEM = {
	0b01111110,
	0b10100001,
	0b10011001,
	0b10000101,
	0b01111110, //0

	0b00000000,
	0b10000010,
	0b11111111,
	0b10000000,
	0b00000000, //1

	0b10000010,
	0b11000001,
	0b10100001,
	0b10010001,
	0b10001110, //2

	0b01000010,
	0b10000001,
	0b10001001,
	0b10001001,
	0b01110110, //3

	0b00011000,
	0b00010100,
	0b00010010,
	0b11111111,
	0b00010000, //4

	0b01001111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110001, //5

	0b01111110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110010, //6

	0b00000001,
	0b11000001,
	0b00110001,
	0b00001101,
	0b00000011, //7

	0b01110110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110110, //8

	0b01000110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01111110, //9

	0b11111110,
	0b00001001,
	0b00001001,
	0b00001001,
	0b11111110, //A

	0b11111111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110110, //B

	0b01111110,
	0b10000001,
	0b10000001,
	0b10000001,
	0b01000010, //C

	0b11111111,
	0b10000001,
	0b10000001,
	0b10000001,
	0b01111110, //D

	0b11111111,
	0b10001001,
	0b10001001,
	0b10001001,
	0b10000001, //E

	0b11111111,
	0b00001001,
	0b00001001,
	0b00001001,
	0b00000001, //F

	0b01111110,
	0b10000001,
	0b10000001,
	0b10010001,
	0b11110010, //G

	0b11111111,
	0b00001000,
	0b00001000,
	0b00001000,
	0b11111111, //H

	0b00000000,
	0b10000001,
	0b11111111,
	0b10000001,
	0b00000000, //I

	0b01100000,
	0b10000000,
	0b10000001,
	0b01111111,
	0b00000000, //J

	0b11111111,
	0b00001000,
	0b00010100,
	0b00100010,
	0b11000001, //K

	0b11111111,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000, //L

	0b11111111,
	0b00000110,
	0b00111000,
	0b00000110,
	0b11111111, //M

	0b11111111,
	0b00000110,
	0b00011000,
	0b01100000,
	0b11111111, //N

	0b01111110,
	0b10000001,
	0b10000001,
	0b10000001,
	0b01111110, //O

	0b11111111,
	0b00001001,
	0b00001001,
	0b00001001,
	0b00000110, //P

	0b01111110,
	0b10000001,
	0b10100001,
	0b01000001,
	0b10111110, //Q

	0b11111111,
	0b00001001,
	0b00001001,
	0b00011001,
	0b11100110, //R

	0b01000110,
	0b10001001,
	0b10001001,
	0b10001001,
	0b01110010, //S

	0b00000001,
	0b00000001,
	0b11111111,
	0b00000001,
	0b00000001, //T

	0b01111111,
	0b10000000,
	0b10000000,
	0b10000000,
	0b01111111, //U

	0b00011111,
	0b01100000,
	0b10000000,
	0b01100000,
	0b00011111, //V

	0b11111111,
	0b01100000,
	0b00011100,
	0b01100000,
	0b11111111, //W

	0b11000011,
	0b00110100,
	0b00001000,
	0b00110100,
	0b11000011, //X

	0b00000011,
	0b00001100,
	0b11110000,
	0b00001100,
	0b00000011, //Y

	0b11000001,
	0b10100001,
	0b10011001,
	0b10000101,
	0b10000011, //Z

	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000, //blank

	0b11111111,
	0b10000001,
	0b10000001,
	0b10000001,
	0b11111111, //unknown
	};
// bytes per char
#define font_width 5
// bytes per char including spaving (which is allways zero and not contained above)
#define font_widthw (font_width+1)


// font is 0-9 A-Z
static const void const* font_pattern(char c, uint8_t index) {
	if (index >= font_width) {
		return (void*)0;
	}
	uint16_t patterni = 0;
	if (c>='0' && c<='9') {
		patterni += c - '0';
	}
	else {
		patterni += 10;
		if (c>='A' && c<='Z') {
			patterni += c - 'A';
		}
		else if (c>='a' && c<='z') {
			patterni += c - 'a';
		}
		else {
			patterni += 26;
			if (c==' ') {
				;
			}
			else {
				patterni++;
			}
		}
	}
	patterni *= font_width;
	patterni += index;
	return font_5x8 + patterni;
}
