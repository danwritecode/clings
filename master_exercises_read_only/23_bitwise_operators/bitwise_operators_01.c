/*
 * Now we will start with bitwise operators, which help you manipulate bits directly.
 * Bitwise operators are essential for low-level programming and are often used in systems programming, embedded systems, and performance-critical code.
 * If you do not know bitwise operators, you can learn more here: https://en.wikipedia.org/wiki/Bitwise_operations_in_C
 *
 * In this exercise, your task is to find the correct bitwise operator so that each result matches the expected value.
 * 
 * Here are some common bitwise operators in C that you might need:
 *   - &  : Bitwise AND
 *   - |  : Bitwise OR
 *   - ^  : Bitwise XOR (exclusive OR)
 *   - ~  : Bitwise NOT (one's complement)
 *   - << : Left shift
 *   - >> : Right shift
 */

// Hint: convert number `a` and `b` to binary. 

#include <assert.h>
#include <limits.h>
#include <stdbool.h>


int main(void) {
	int a = 5;
	int b = 2;

	int f = a  2; // <-- Fix here (hint: multiply `a` by 2^2)
	assert(f == 20); // f should be 20 ...

	int e = a b; // <-- Fix here
	assert(e == 7);

	int c = a  b; // <-- Fix here
	assert(c == 0);

	int k = -1;
	int g =     // <-- Fix here: (use k somehow)
	assert(g == 0);

	int d = a b; // <-- Fix here
	assert(d == 7);

	return 0;
}
