/** LEARNING
 * Your goal is to understand how the for statement works.
 *
 * The for statement has the following syntax:
 *
 * for (initialization; condition; increment) {
 *		statement;
 * 	 	statement;
 * 	 	...
 * }
 *
 * The for statement is equivalent to the following while statement:
 *
 * initialization;
 * while (condition) {
 *		statement;
 * 		statement;
 * 		...
 *		increment;
 *	}
 */

/** EXERCISE
 * Your job is to write a for statement equivalent to the following 
 * while statement:
 *
 * i = 0; // initialization
 * while (i < 10) { // condition
 *	printf("%d\n", i);
 *	verify_count(&count, i);
 *	i++; // increment
 * }
 */

// ❌ I AM NOT DONE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT CHANGE THIS
static int track = 0, count = 0;

// DO NOT CHANGE THIS
void verify_count (int *count, int i) {
	assert(i == track++);
	(*count)++;
}

int main() {
	int i = rand() % 100 + 11; // DO NOT CHANGE THIS

	// YOUR CODE HERE
	for (initialization; condition; increment) {
	// END YOUR CODE
		printf("%d\n", i);
		verify_count(&count, i); // DO NOT CHANGE THIS
	}

	// BONUS: print the value of i here and try to understand why it's 10

	// DO NOT CHANGE THIS
	assert (count == 10);
	return 0;
}

