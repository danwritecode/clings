/*
 * This file does not have any mistakes.
 * Here you can see the prepared `get_line` function.
 * Replace the for loop with a loop that does not use && or ||.
 *
 * This exercise will help you understand operator precedence.
 *
 */

// ❌ I AM NOT DONE
// Hint: Do not use for loop!

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LIM 35


int get_line(char s[],int lim) {
	FILE *f = fopen("./exercises/20_relational_logical_operators/README.md", "r");
	if (!f) {
		perror("Failed to open a file");
		return 0;
	}

	// YOUR CODE HERE
	int i, c;

	for (i=0; i < lim-1 && (c=fgetc(f))!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	//END YOUR CODE

	fclose(f);
	return i;
}

int main() {
	//DO NOT CHANGE
	char line[LIM];
	char ref[] = "# Relational and logical Operators";

	get_line(line, LIM);

	for(int i = 0; i < LIM; i++) {
		printf("%c", line[i]);
	}
	printf("\n");

	assert(strcmp(line, ref) == 0);

	return 0;
}
