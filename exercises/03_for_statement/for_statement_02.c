/*
 * The provided program generates a table of 
 * temperatures in Fahrenheit and their corresponding 
 * Celsius equivalents, increasing in steps of 20 degrees from 
 * 0°F to 300°F. The Celsius temperature is calculated directly 
 * within the printf statement using a for loop.
 *
 * Modify the provided temperature conversion 
 * C program to print the Fahrenheit to Celsius c
 * onversion table in reverse order, 
 * from 0 degrees Fahrenheit up to 300 degrees.
*/

// ❌ I AM NOT DONE

#include <stdio.h>
#include <assert.h>

#define TRACK 320

static int track = 0;

// DO NOT CHANGE THIS
void verify_count (int i) {
	assert(i == track);
	track += 20;
}

int main() {
	// YOUR CODE HERE
	for (int fahr = 300; fahr >= 0; fahr -= 20) {
	// END YOUR CODE
		printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

		verify_count(fahr); // DO NOT CHANGE THIS
	}

	// BONUS: print the value of track here 
	// and try to understand why it's 320

	// DO NOT CHANGE THIS
	assert (track == TRACK);

	return 0;
}

