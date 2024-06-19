/*
 * The goal of this exercise is to understand how to use logical operators.
 * Fix the `evaluate_logical` function so it returns the correct value.
 */

// ❌ I AM NOT DONE

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

bool evaluate_logical(bool a, bool b, bool c) {
    return a  b  c; // <-- Fix here
}

int main() {
	// Only 'a' is true, should return false
    assert(evaluate_logical(true, false, false) == false);

	// etc.
    assert(evaluate_logical(false, true, false) == false);
    assert(evaluate_logical(false, false, true) == true);
    assert(evaluate_logical(false, false, false) == false);
    assert(evaluate_logical(true, true, true) == true);
    
    printf("All tests passed.\n");
    return 0;
}
