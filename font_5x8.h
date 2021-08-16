// original code by LadyAda (and other contributors?)
// modified with font/string support by sparr
// subject to the license of the MiniPOV3 project


// font inspired by many 5x8 fonts from various sources
const unsigned char font[64*5] PROGMEM = {
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

 0b00100000,
 0b01010100,
 0b01010100,
 0b01010100,
 0b01111000, //a

 0b01111111,
 0b01000100,
 0b01000100,
 0b01000100,
 0b00111000, //b

 0b00111000,
 0b01000100,
 0b01000100,
 0b01000100,
 0b00101000, //c

 0b00111000,
 0b01000100,
 0b01000100,
 0b01000100,
 0b01111111, //d

 0b00111000,
 0b01010100,
 0b01010100,
 0b01010100,
 0b01001000, //e

 0b00000100,
 0b01111110,
 0b00000101,
 0b00000001,
 0b00000000, //f

 0b10011000,
 0b10100100,
 0b10100100,
 0b10100100,
 0b01111000, //g

 0b01111111,
 0b00000100,
 0b00000100,
 0b00000100,
 0b01111000, //h

 0b00000000,
 0b00000000,
 0b01111010,
 0b00000000,
 0b00000000, //i

 0b00000000,
 0b01000000,
 0b10000000,
 0b01111010,
 0b00000000, //j

 0b01111111,
 0b00010000,
 0b00101000,
 0b01000100,
 0b00000000, //k

 0b00000000,
 0b00000000,
 0b01111111,
 0b00000000,
 0b00000000, //l

 0b01111000,
 0b00000100,
 0b00001000,
 0b00000100,
 0b01111000, //m

 0b01111100,
 0b00001000,
 0b00000100,
 0b00000100,
 0b01111000, //n

 0b00111000,
 0b01000100,
 0b01000100,
 0b01000100,
 0b00111000, //o

 0b11111100,
 0b00100100,
 0b00100100,
 0b00100100,
 0b00011000, //p

 0b00011000,
 0b00100100,
 0b00100100,
 0b00100100,
 0b11111100, //q

 0b01111100,
 0b00001000,
 0b00000100,
 0b00000100,
 0b00000100, //r

 0b01001000,
 0b01010100,
 0b01010100,
 0b01010100,
 0b00100100, //s

 0b00000000,
 0b00000100,
 0b01111111,
 0b01000100,
 0b00000000, //t

 0b00111100,
 0b01000000,
 0b01000000,
 0b01000000,
 0b00111100, //u

 0b00001100,
 0b00110000,
 0b01000000,
 0b00110000,
 0b00001100, //v

 0b00111100,
 0b01000000,
 0b00110000,
 0b01000000,
 0b00111100, //w

 0b01000100,
 0b00101000,
 0b00010000,
 0b00101000,
 0b01000100, //x

 0b10011100,
 0b10100000,
 0b10100000,
 0b10100000,
 0b01111100, //y

 0b01000100,
 0b01100100,
 0b01010100,
 0b01001100,
 0b01000100, //z

 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000,
 0b00000000, //blank

 0b11111111,
 0b11111111,
 0b11111111,
 0b11111111,
 0b11111111 //unknown

};

/*	// decode sample
	// read one column from ROM
	if(j%6<5) {
		out = pgm_read_byte(text_string_p + j/6); // the character we are on
		out = pgm_read_byte(
			font_p + (
				(out>='0'&&out<='9')?(out-'0'):
				(out>='A'&&out<='Z')?(out-'A'+10):
				(out>='a'&&out<='z')?(out-'a'+36):
				(out==' ')?(62):(63)
		) * 5 + j % 6); // one column from the character
	} else {
		out = 0; // blank column between letters
	}
*/
