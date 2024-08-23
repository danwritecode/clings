/*
 * Fix this short program, which checks for a leap year.
 * 
 * You can only delete or edit lines with the comment "// <-- Fix this line".
 * Ensure the program correctly identifies leap years according to the following rules:
 * 1. A year is a leap year if it is divisible by 4.
 * 2. However, if the year is also divisible by 100, it is not a leap year unless it is also divisible by 400.
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// ❌ I AM NOT DONE

int main() {

	int year = 2024;
	bool isLeap = false;

	if ((year / 4 == 0 && year % 100 == 0) || year % 400 == 0) { // <-- Fix this line
		isLeap = true;
		printf("%d is a leap year\n", year);
	} else {
		isLeap = false;
		printf("%d is not a leap year\n", year);
	}


	assert(isLeap == true);

	return 0;
}
