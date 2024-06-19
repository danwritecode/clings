/*
 * Fix the program
 * 
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// ❌ I AM NOT DONE

int main() {
	int a = 1;
    int b = 2;
    int c = 3;
    int result;

    // Only add parentheses, so that result == 2
    result = b * c / a - b % c; // <-- Fix this line 

    assert(result == 2);
    printf("The result is %d\n", result);

    return 0;
}

