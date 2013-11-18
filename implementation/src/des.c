#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "des.h"

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



