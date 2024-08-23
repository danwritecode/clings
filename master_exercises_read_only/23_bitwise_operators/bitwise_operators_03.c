/*
 * Now let's try to create a bit mask that will mask out (set to 0) the lower four bits of a byte (8 bits).
 * In other words, we want to keep the upper 4 bits unchanged and set the lower 4 bits to 0.
 *
 * Example:
 * 
 * Let's say we have the following byte:
 * i = 10111011
 * 
 * After applying the bit mask to clear the lower four bits, we should get:
 * result = 10110000
 * 
 * Steps:
 * 1. Create a bit mask that has 1s in the upper four bit positions and 0s in the lower four bit positions.
 * 2. Apply the mask to the given byte using the bitwise AND operator.
 */


#include <assert.h>
#include <limits.h>
#include <stdio.h>

void print_bits(unsigned char num) {
	printf("%3d: ", num);
	for(long i = sizeof(num) * CHAR_BIT - 1; i >= 0; i--) {
		printf("%d ", (num >> i) & 1);
	}

	printf("\n");
}

int main(void) {
	
	unsigned char i = 0xBB; // 10111011
	print_bits(i);

	unsigned char mask = ; // <-- Fix here
	i = i  mask; // <-- Fix here

	print_bits(i); 
	assert(i == 0xB0);	  // 10110000

	return 0;
}
