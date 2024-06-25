/*
 * This expression:
 * a = a + 1
 * can be written like this:
 * a += 1
 *
 * The += operator is an assignment operator.
 *
 * Most binary operators have corresponding assignment operators.
 * These can be useful for writing cleaner and more understandable code.
 */

// ❌ I AM NOT DONE

#include <assert.h>
#include <stdbool.h>

int main() {
	int a = 4;
	int b = 1;

	a = a / 2; // <-- Fix here (use an assignment operator)
	b = b * 3; // <-- Fix here (use an assignment operator)

	assert(a == 2);
	assert(b == 3);
	return 0;
}
