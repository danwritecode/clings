/* Now we will start with bitwise operators, which helps you manipulate bits.
 * If you do not know bitwise operators look here: https://en.wikipedia.org/wiki/Bitwise_operations_in_C
 *
 * Let's start with simple example.
 * Fix `is_even` function, which returns true if number is even.
 * Of course we could use %, but we are smarter!
 * Write down even and odd numbers in binary and try to find pattern, which you could use for deciding if number is even or not.
 * Decide which bitwise operator would work.
 *
 */
 

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

void print_bits(char num) {
	printf("%d: ", num);
	for(long i = sizeof(num) * CHAR_BIT - 1; i >= 0; i--) {
		printf("%d ", (num >> i) & 1);
	}

	printf("\n");
}

bool is_even(int num) {
	// Pay attention to operator precendence
	if(num  1 == 0) { // <-- Fix here
		return true;
	}

	return false;
}

int main(void) {
	char num = 7;
	print_bits(num);
	print_bits(1);

	assert(is_even(num) == 0);
	
	return 0;
}
