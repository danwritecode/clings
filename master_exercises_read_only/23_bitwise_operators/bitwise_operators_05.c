/*
 * Bit Manipulation Exercise: Swap Most Significant Bit (MSB) and Least Significant Bit (LSB)
 *
 * Your task is to implement the `swap_edge_bits` function, which swaps the MSB and LSB of an 8-bit unsigned char.
 *
 * MSB = Most Significant Bit (leftmost bit)
 * LSB = Least Significant Bit (rightmost bit)
 *
 * Example:
 *
 * Input:  10000000 (decimal 128)
 * Output: 00000001 (decimal 1)
 *
 * The function should follow these steps:
 * 1. Extract the MSB, move to LSB
 * 2. Extract the LSB, move to MSB
 * 3. Create a mask to clear both MSB and LSB
 * 4. Combine the extracted bits with the masked value
 *
 * This exercise demonstrates bitwise operations and manipulations on individual bits.
 */

// ❌ I AM NOT DONE

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

// unsigned char has 8 bits
unsigned char swap_edge_bits(unsigned char num) {
	unsigned char msb = ; // <-- Fix here
	unsigned char lsb = ; // <-- Fix here
	unsigned char mask = ; // <-- Fix here

	num = num  mask  msb  lsb; // <-- Fix here
	
	return num;
}


int main(void) {
	
	unsigned char i = 128;
	print_bits(i);

	i = swap_edge_bits(i);

	print_bits(i); 
	assert(i == 1);

	return 0;
}
