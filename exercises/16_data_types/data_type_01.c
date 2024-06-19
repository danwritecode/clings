/*
 * In this exercise, you will practice understanding data types and sizes in C.
 * The basic data types in C include `char`, `int`, `float`, and `double`.
 * You can also apply qualifiers like `short`, `long`, `signed`, and `unsigned` to these types,
 * which affect their size and behavior. Understanding how these types and qualifiers
 * work at a binary level is crucial for robust C programming.
 *
 * The provided file will not compile or run correctly until
 * the user fixes the mistakes.
 * (You can only delete/edit lines with // <-- Fix this line)
*/

// ❌ I AM NOT DONE

#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

 // Note: Carefully observe the output to understand the underlying behavior caused by type limits and conversions.
 // |char| <= |short| <= |int| <= |long| <= |long long|

int main() {
    unsigned int negativeAsUnsigned = -5; // <-- Fix this kind of misuse

    long long veryLargeNumber = 9223372036854775807;
    printf("Maximum long long value: %l\n", veryLargeNumber); // <-- Fix this line

    printf("Range of unsigned long long: 0 to %llu\n", ); // <-- Fix this line (use symbolic constant limits.h)
    printf("Range of signed long long: %lld to %lld\n", ); // <-- Fix this line (use symbolic constant)
    printf("Range of unsigned char: %d to %d\n", ); // <-- Fix this line (Write a number)
    printf("Range of signed char: %d to %d\n", ); // <-- Fix this line (write a number)

    double floatingPointNumber = 0.999999;
    int integerRepresentation = floatingPointButNotReally; // <-- Fix this line (use floatingPointNumber)
    printf("Double to int casting result: %d\n", integerRepresentation);

	bool understand = false;
	unsigned int plus_one = 1;
	int minus_one = -1;

	if(plus_one > minus_one) { // <-- Fix this line
		understand = true;
	} 
	assert(understand);

	return 0;
}
