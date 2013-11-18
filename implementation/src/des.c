#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "des.h"


#define FAIL 	0xCA

// Partially tested
uint64_t expand_input(uint32_t input) {
	/* From 32 bits in input, outputs 48 bits according
	 * to the expansion function defined in DES. */

	uint64_t output;
	output = 0;

	/* 
		Let consider input =   [01 02 03 04 05 06 07 08
					09 10 11 12 13 14 15 16
					17 18 19 20 21 22 23 24
					25 26 27 28 29 30 31 32]  => Représentation en mémoire
	*/	

	
	/*			32		    01 02 03 04 05		04 05			*/
	char oct1 = (char) (((input & 0x01) << 7) | ((input >> 27) << 2) | ((input >> 27) & 0x03));
	/* 			06 07 08 09	            08 09 10 11					*/
	char oct2 = (char) (((input >> 23) & 0x0F) << 4 | ((input >> 21) & 0x0F));
	/* 			       	12 13		12 13 14 15 16 17				*/
	char oct3 = (char) (((input >> 19) & 0x3) << 6 | ((input >> 15) & 0x3F));
	/* 		        16 17 18 19 20 21 		20 21 					*/
	char oct4 = (char) ((input >> 11 & 0x3f) << 2 | ((input >> 11) & 0x03));
	/* 			    22 23 24 25 		24 25 26 27 				*/
	char oct5 = (char) (((input >> 7) & 0x0F) << 4 | ((input >> 5) & 0x0F));	
	/* 				28 29 		    28 29 30 31 32 	    1 			*/
	char oct6 = (char) (((input >> 3) & 0x3) << 6 | (input & 0x1F) << 1 | input >> 31);

	return (uint64_t) oct1 << 40 | (uint64_t) oct2 << 32 | (uint64_t) oct3 << 24 | 
		(uint64_t) oct4 << 16 | (uint64_t) oct5 << 8 | (uint64_t) oct6;
}


uint8_t get_bit(uint32_t n, uint8_t i) {
	/* Return the ith bit of an int n ; assuming that n = [ 01 02 03 .. 31 32 ]
	 * It means that get_bit(0x02, 2) will return 0, and get_bit(0x02, 31) will return 1;
	 *
	 * If i is not a correct value, then it returns 0xCA */
	
	if (i > 32) {
		return FAIL;
	}

	return (uint8_t) ((n >> (32 - i)) & 0x01);

}

// To be tested
uint32_t permutation(uint32_t input) {

	char oct1 = (char) (get_bit(input, 16) << 7 | get_bit(input, 7) << 6 | get_bit(input, 20) << 5 | get_bit(input, 21) << 4 | get_bit(input, 29) << 3 | get_bit(input, 12) << 2 | get_bit(input, 28) << 1 | get_bit(input, 17));
	char oct2 = (char) (get_bit(input, 1) << 7 | get_bit(input, 15) << 6 | get_bit(input, 23) << 5 | get_bit(input, 26) << 4 | get_bit(input, 5) << 3 | get_bit(input, 18) << 2 | get_bit(input, 31) << 1 | get_bit(input, 10));
	char oct3 = (char) (get_bit(input, 2) << 7 | get_bit(input, 8) << 6 | get_bit(input, 24) << 5 | get_bit(input, 14) << 4 | get_bit(input, 32) << 3 | get_bit(input, 27) << 2 | get_bit(input, 3) << 1 | get_bit(input, 9));
	char oct4 = (char) (get_bit(input, 19) << 7 | get_bit(input, 13) << 6 | get_bit(input, 30) << 5 | get_bit(input, 6) << 4 | get_bit(input, 22) << 3 | get_bit(input, 11) << 2 | get_bit(input, 4) << 1 | get_bit(input, 25));

	return (uint32_t) oct1 << 24 | (uint32_t) oct2 << 16 | (uint32_t) oct3 << 8 | (uint32_t) oct4;

}
