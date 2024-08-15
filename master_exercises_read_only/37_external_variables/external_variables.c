/*
 * Exercise: Understanding and Fixing External Variables
 *
 * In this exercise, you'll work with a simple program that uses external variables
 * to keep track of a counter across multiple function calls. The program is currently
 * broken and doesn't produce the expected output.
 *
 * Your tasks:
 * 1. Identify why the counter is not incrementing correctly.
 * 2. Fix the issue by correctly using external variables.
 * 3. Make sure the assert statements pass after your implementation.
 *
 * Tips:
 * - Pay attention to variable declarations and their scope.
 * - Remember that external variables are defined outside of any function.
 */

// ❌ I AM NOT DONE

#include <stdio.h>
#include <assert.h>

// TODO: Fix the counter variable declaration

void increment_counter() {
    int counter = 0;
    counter++;
}

int get_counter() {
    // TODO: Fix this function to return the correct counter value
    return 0;
}

void reset_counter() {
    // TODO: Implement this function to reset the counter to 0
}

int main() {
    assert(get_counter() == 0);
    
    increment_counter();
    increment_counter();
    assert(get_counter() == 2);
    
    increment_counter();
    assert(get_counter() == 3);
    
    reset_counter();
    assert(get_counter() == 0);
    
    increment_counter();
    assert(get_counter() == 1);

    printf("All tests passed!\n");
    return 0;
}
