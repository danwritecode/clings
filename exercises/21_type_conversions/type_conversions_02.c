/*
 * In this exercise, you will correct the issues in the given program.
 * The program should convert all lowercase letters in a string to uppercase.
 * Your task is to implement the correct logic in the `to_upper` function.
 *
 * Do not add any library.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

// ❌ I AM NOT DONE
// hint: Take a look at ASCII table

char to_upper(char c) {
    if(c  'a' && c  'z') {  // <-- Fix here
			    // <-- Fix here
    }
    
    return c;
}


int main() {
    char s[] = "hello, world!";

    for(int i = 0, len = strlen(s); i < len; i++) {
	s[i] = to_upper(s[i]);
    }

    printf("%s\n", s);

    assert(strcmp(s, "HELLO, WORLD!") == 0);
    return 0;
}
