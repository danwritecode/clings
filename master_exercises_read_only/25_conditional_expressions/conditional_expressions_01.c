/*
 * Rewrite the `to_upper` function from the previous exercise without using an `if` statement.
 * Instead, use a conditional (ternary) expression.
 *
 * A conditional expression looks like this:
 * condition ? value_if_true : value_if_false
 *
 * For example:
 * z = (a > b) ? a : b;
 *
 * In this example, if `a` is greater than `b`, then `z` will be assigned the value of `a`.
 * Otherwise, `z` will be assigned the value of `b`.
 *
 * Conditional expressions can sometimes make the code easier to read.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

// ❌ I AM NOT DONE

char to_upper(char c) {
	// Rewrite
	if(c >= 'a' && c <= 'z') {
		return c - 32;
	}

	return c;
	// Rewrite
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
