/*
 * This program demonstrates the use of increment (++) and decrement (--) operators in C.
 * The increment operator adds 1 to its operand, while the decrement operator subtracts 1.
 * The unusual aspect is that these operators can be used either as prefix or postfix.
 * 
 * Prefix (e.g., ++i): Increment/decrement first, then return the new value.
 * Postfix (e.g., i++): Return the current value first, then increment/decrement.
 */

// ❌ I AM NOT DONE

#include <assert.h>
#include <stdbool.h>

int main() {
	int i = 0;
	int j = 2;
	int k = 0;
	int l = 3;

	// Use ++/-- instead
	i = i + 1; // <-- Fix here 
	j = j - 1; // <-- Fix here 
	
	// DO NOT CHANGE
	assert(i == 1);
	assert(j == 1);
	
	k = (i+j)++; // <-- Fix bug
	
	i = l++; // <-- Fix bug

	// DO NOT CHANGE
	assert(i == 4);
	assert(j == 1);
	assert(k == 2);
	assert(l == 4);

	return 0;
}
