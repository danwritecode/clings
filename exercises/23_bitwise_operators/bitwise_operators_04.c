/*
 * XOR Swap Algorithm
 *
 * The XOR (exclusive or) operator has special properties that allow us to swap two values
 * without using a temporary variable. This technique is called the XOR swap.
 *
 * How XOR works:
 * - When you XOR a bit with 0, it remains unchanged
 * - When you XOR a bit with 1, it flips (0 becomes 1, and 1 becomes 0)
 * - XOR is commutative: a XOR b = b XOR a
 * - XOR is associative: (a XOR b) XOR c = a XOR (b XOR c)
 *
 * Example:
 * Let a = 1010 and b = 0011
 * Step 1: a = a XOR b  ->  a = 1010 XOR 0011 = 1001,  b = 0011
 * Step 2: b = a XOR b  ->  a = 1001,  b = 1001 XOR 0011 = 1010
 * Step 3: a = a XOR b  ->  a = 1001 XOR 1010 = 0011,  b = 1010
 *
 * Result: The values of 'a' and 'b' have been swapped.
 *
 * Task: Use these properties of XOR to swap the values of 'a' and 'b' without using a temporary variable.
 */

// ❌ I AM NOT DONE

#include <assert.h>

int main(void) {
	
	int a = 11;
	int b = 42;

	if(a == b) return 0;

	// Fix code
	a = a ^ b;
	
	a = a ^ b;
	// Fix code


	assert(a == 42);
	assert(b == 11);

	return 0;
}
