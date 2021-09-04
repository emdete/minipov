/*****************************************************************
 * Font from SYSVbanner.c
 *
 * This is a PD version of the SYS V banner program (at least I think
 * it is compatible to SYS V) which I wrote to use with the clock
 * program written by:
 **     DCF, Inc.
 **     14623 North 49th Place
 **     Scottsdale, AZ 85254
 * and published in the net comp.sources.misc newsgroup in early July
 * since the BSD banner program works quite differently.
 *
 * There is no copyright or responsibility accepted for the use
 * of this software.
 *
 * Brian Wallis, brw@jim.odr.oz, 4 July 1988
 *
 *****************************************************************
 * Changes by David Frey, david@eos.lugs.ch, 3 February 1997:
 * 1. protoized and indented, 2. changed @ character to #
 *****************************************************************
 * changed to binary & optimized structure (c) mdt@emdete.de, Aug 2021
 *****************************************************************
 */

const unsigned char font_sysv[][8] = {{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1100111,
	0b1101111,
	0b1100111,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000011,
	0b0000111,
	0b0000011,
	0b0000000,
	0b0000011,
	0b0000111,
	0b0000011,
	},{
	0b0000000,
	0b0010100,
	0b0010100,
	0b1111111,
	0b0010100,
	0b1111111,
	0b0010100,
	0b0010100,
	},{
	0b0000000,
	0b0100110,
	0b1001001,
	0b1001001,
	0b1111111,
	0b1001001,
	0b1001001,
	0b0110010,
	},{
	0b0000000,
	0b1000111,
	0b0100101,
	0b0010111,
	0b0001000,
	0b1110100,
	0b1010010,
	0b1110001,
	},{
	0b0000000,
	0b0110000,
	0b1001010,
	0b1001101,
	0b1001101,
	0b1010010,
	0b0100000,
	0b1010000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0001011,
	0b0000111,
	0b0000011,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0011100,
	0b0100010,
	0b1000001,
	0b1000001,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1000001,
	0b1000001,
	0b0100010,
	0b0011100,
	0b0000000,
	},{
	0b0000000,
	0b0001000,
	0b0101010,
	0b0011100,
	0b0000000,
	0b0011100,
	0b0101010,
	0b0001000,
	},{
	0b0000000,
	0b0000000,
	0b0001000,
	0b0001000,
	0b0111110,
	0b0001000,
	0b0001000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1011000,
	0b0111000,
	0b0011000,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1110000,
	0b1110000,
	0b1110000,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b1000000,
	0b0100000,
	0b0010000,
	0b0001000,
	0b0000100,
	0b0000010,
	0b0000001,
	},{
	0b0000000,
	0b0011100,
	0b0100010,
	0b1000101,
	0b1001001,
	0b1010001,
	0b0100010,
	0b0011100,
	},{
	0b0000000,
	0b0000000,
	0b1000100,
	0b1000010,
	0b1111111,
	0b1000000,
	0b1000000,
	0b0000000,
	},{
	0b0000000,
	0b1110010,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1000110,
	},{
	0b0000000,
	0b0100010,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0110110,
	},{
	0b0000000,
	0b0001111,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b1111110,
	0b0001000,
	},{
	0b0000000,
	0b0100111,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0110001,
	},{
	0b0000000,
	0b0111110,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0110010,
	},{
	0b0000000,
	0b0000011,
	0b0000001,
	0b1110001,
	0b0001001,
	0b0000101,
	0b0000011,
	0b0000001,
	},{
	0b0000000,
	0b0110110,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0110110,
	},{
	0b0000000,
	0b0100110,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0111110,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0100010,
	0b1010101,
	0b0100010,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1011011,
	0b0111011,
	0b0011011,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0001000,
	0b0010100,
	0b0100010,
	0b1000001,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0010100,
	0b0010100,
	0b0010100,
	0b0010100,
	0b0010100,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1000001,
	0b0100010,
	0b0010100,
	0b0001000,
	0b0000000,
	},{
	0b0000000,
	0b0000010,
	0b0000001,
	0b0000001,
	0b1010001,
	0b0001001,
	0b0001001,
	0b0000110,
	},{
	0b0000000,
	0b0111110,
	0b1000001,
	0b1011101,
	0b1010101,
	0b1011101,
	0b1010001,
	0b0101110,
	},{
	0b0000000,
	0b1111000,
	0b0010100,
	0b0010010,
	0b0010001,
	0b0010010,
	0b0010100,
	0b1111000,
	},{
	0b0000000,
	0b1111111,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0110110,
	},{
	0b0000000,
	0b0111110,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b0100010,
	},{
	0b0000000,
	0b1111111,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b0111110,
	},{
	0b0000000,
	0b1111111,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1000001,
	0b1000001,
	},{
	0b0000000,
	0b1111111,
	0b0001001,
	0b0001001,
	0b0001001,
	0b0001001,
	0b0000001,
	0b0000001,
	},{
	0b0000000,
	0b0111110,
	0b1000001,
	0b1000001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0111010,
	},{
	0b0000000,
	0b1111111,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b1111111,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1000001,
	0b1111111,
	0b1000001,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0110000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b0111111,
	},{
	0b0000000,
	0b1111111,
	0b0001000,
	0b0001000,
	0b0010100,
	0b0100010,
	0b1000001,
	0b0000000,
	},{
	0b0000000,
	0b1111111,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	},{
	0b0000000,
	0b1111111,
	0b0000010,
	0b0000100,
	0b0001000,
	0b0000100,
	0b0000010,
	0b1111111,
	},{
	0b0000000,
	0b1111111,
	0b0000010,
	0b0000100,
	0b0001000,
	0b0010000,
	0b0100000,
	0b1111111,
	},{
	0b0000000,
	0b1111111,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1111111,
	},{
	0b0000000,
	0b1111111,
	0b0001001,
	0b0001001,
	0b0001001,
	0b0001001,
	0b0001001,
	0b0000110,
	},{
	0b0000000,
	0b0111110,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1010001,
	0b0100001,
	0b1011110,
	},{
	0b0000000,
	0b1111111,
	0b0001001,
	0b0001001,
	0b0001001,
	0b0011001,
	0b0101001,
	0b1000110,
	},{
	0b0000000,
	0b0100110,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b1001001,
	0b0110010,
	},{
	0b0000000,
	0b0000001,
	0b0000001,
	0b0000001,
	0b1111111,
	0b0000001,
	0b0000001,
	0b0000001,
	},{
	0b0000000,
	0b0111111,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b0111111,
	},{
	0b0000000,
	0b0001111,
	0b0010000,
	0b0100000,
	0b1000000,
	0b0100000,
	0b0010000,
	0b0001111,
	},{
	0b0000000,
	0b0111111,
	0b1000000,
	0b1000000,
	0b0111110,
	0b1000000,
	0b1000000,
	0b0111111,
	},{
	0b0000000,
	0b1000001,
	0b0100010,
	0b0010100,
	0b0001000,
	0b0010100,
	0b0100010,
	0b1000001,
	},{
	0b0000000,
	0b0000001,
	0b0000010,
	0b0000100,
	0b1111000,
	0b0000100,
	0b0000010,
	0b0000001,
	},{
	0b0000000,
	0b1000001,
	0b1100001,
	0b1010001,
	0b1001001,
	0b1000101,
	0b1000011,
	0b1000001,
	},{
	0b0000000,
	0b0000000,
	0b1111111,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b0000000,
	},{
	0b0000000,
	0b0000001,
	0b0000010,
	0b0000100,
	0b0001000,
	0b0010000,
	0b0100000,
	0b1000000,
	},{
	0b0000000,
	0b0000000,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1000001,
	0b1111111,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000100,
	0b0000010,
	0b0000001,
	0b0000010,
	0b0000100,
	0b0000000,
	},{
	0b0000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000011,
	0b0000111,
	0b0001011,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b1111000,
	0b0010100,
	0b0010010,
	0b0010010,
	0b0010100,
	0b1111000,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b1001010,
	0b1001010,
	0b1001010,
	0b1001010,
	0b0110100,
	},{
	0b0000000,
	0b0000000,
	0b0111100,
	0b1000010,
	0b1000010,
	0b1000010,
	0b1000010,
	0b0100100,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b1000010,
	0b1000010,
	0b1000010,
	0b1000010,
	0b0111100,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b1001010,
	0b1001010,
	0b1001010,
	0b1001010,
	0b1000010,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0001010,
	0b0001010,
	0b0001010,
	0b0001010,
	0b0000010,
	},{
	0b0000000,
	0b0000000,
	0b0111100,
	0b1000010,
	0b1000010,
	0b1010010,
	0b1010010,
	0b0110100,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0001000,
	0b0001000,
	0b0001000,
	0b0001000,
	0b1111110,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b1111110,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0100000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b0111110,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0001000,
	0b0001000,
	0b0011000,
	0b0100100,
	0b1000010,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0000100,
	0b0001000,
	0b0001000,
	0b0000100,
	0b1111110,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0000100,
	0b0001000,
	0b0010000,
	0b0100000,
	0b1111110,
	},{
	0b0000000,
	0b0000000,
	0b0111100,
	0b1000010,
	0b1000010,
	0b1000010,
	0b1000010,
	0b0111100,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0010010,
	0b0010010,
	0b0010010,
	0b0010010,
	0b0001100,
	},{
	0b0000000,
	0b0000000,
	0b0111100,
	0b1000010,
	0b1000010,
	0b1010010,
	0b0100010,
	0b1011100,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0010010,
	0b0010010,
	0b0010010,
	0b0110010,
	0b1001100,
	},{
	0b0000000,
	0b0000000,
	0b0100100,
	0b1001010,
	0b1001010,
	0b1001010,
	0b1001010,
	0b0110000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000010,
	0b0000010,
	0b1111110,
	0b0000010,
	0b0000010,
	},{
	0b0000000,
	0b0000000,
	0b0111110,
	0b1000000,
	0b1000000,
	0b1000000,
	0b1000000,
	0b0111110,
	},{
	0b0000000,
	0b0000000,
	0b0011110,
	0b0100000,
	0b1000000,
	0b1000000,
	0b0100000,
	0b0011110,
	},{
	0b0000000,
	0b0000000,
	0b1111110,
	0b0100000,
	0b0010000,
	0b0010000,
	0b0100000,
	0b1111110,
	},{
	0b0000000,
	0b0000000,
	0b1000010,
	0b0100100,
	0b0011000,
	0b0011000,
	0b0100100,
	0b1000010,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000010,
	0b0000100,
	0b1111000,
	0b0000100,
	0b0000010,
	},{
	0b0000000,
	0b0000000,
	0b1000010,
	0b1100010,
	0b1010010,
	0b1001010,
	0b1000110,
	0b1000010,
	},{
	0b0000000,
	0b0001000,
	0b0111110,
	0b1000001,
	0b1000001,
	0b1000001,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b0000000,
	0b1110111,
	0b0000000,
	0b0000000,
	0b0000000,
	},{
	0b0000000,
	0b0000000,
	0b0000000,
	0b1000001,
	0b1000001,
	0b1000001,
	0b0111110,
	0b0001000,
	},{
	0b0000000,
	0b0000010,
	0b0000001,
	0b0000001,
	0b0000010,
	0b0000100,
	0b0000100,
	0b0000010,
	},{
	0b0000000,
	0b1010101,
	0b0101010,
	0b1010101,
	0b0101010,
	0b1010101,
	0b0101010,
	0b1010101,
	},{
0
}};

void print_letter_sysv(unsigned char out) {
}
