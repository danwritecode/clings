/*
 * In this exercise, you will correct the issues in the given program.
 * The program should convert all lowercase letters in a string to uppercase.
 * Your task is to implement the correct logic in the `to_upper` function.
 *
 * We will use the properties of a char. A char has a size of 1 byte (8 bits), 
 * so it can store numbers from -128 to 127 if signed, or 0 to 255 if unsigned.
 * If plain char is signed or unsigned is machine-dependent.
 * Printable characters are always positive.
 *
 * When you define a char, C actually stores it as an integer underneath.
 * To display characters, each char is mapped to a number using the ASCII table.
 * The ASCII table maps numbers from 0-127 to specific characters.
 * For example, the character 'A' is mapped to the number 65, and the character 'a' is mapped to the number 97.
 * We can use this mapping to our advantage to convert lowercase letters to uppercase.
 *
 * 1. Check if the letter is lowercase.
 * 2. Convert the letter to uppercase
 *
 * Do not add any libraries.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

// ❌ I AM NOT DONE
// hint: Take a look at ASCII table

char to_upper(char c) {
    // We can actually campare chars (because in memory they are just numbers)
    if(c  'a' && c  'z') {  // <-- 1. Fix here
			    // <-- 2. Fix here
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
