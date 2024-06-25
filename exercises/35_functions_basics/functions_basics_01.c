/*
 * Exercise: Implementing the strlen function
 * 
 * In this exercise, you'll create your own version of the strlen function,
 * which counts the number of characters in a string (excluding the null terminator).
 * 
 * Your tasks:
 * 1. Complete the my_strlen function to return the length of the input string.
 * 2. Move the length calculation logic from main() into the my_strlen function.
 * 3. Ensure the assert statement passes after your implementation.
 * 
 * Tips:
 * - A string in C is terminated by a null character '\0'.
 * - The function should return an int (the length of the string).
 */

// ❌ I AM NOT DONE

#include <assert.h>

// TODO: Finish the function
my_strlen(char *s) {

	return;
}
// Finish the function


int main(void) {
	char *s = "Hello, world!";

	// TODO: Put into my_strlen function
	int len = 0;
	for(int i = 0; s[i] != '\0'; i++) {
		len++;
	}
	// Put into my_strlen function

	//DO NOT CHANGE
	assert(my_strlen(s) == 13);

	return 0;
}
