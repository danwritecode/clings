/*
 * In programming, hardcoding numbers directly into your code 
 * (often referred to as "magic numbers") can make the code less 
 * understandable and harder to maintain.
 *
 * Using symbolic constants can help alleviate these issues by 
 * providing meaningful names for these numbers.
 * 
 * Below is a simple C program that prints a Fahrenheit-to-Celsius 
 * conversion table. The program currently uses magic numbers. 
 * Your task is to refactor this program to use symbolic constants.
 *
 * Example macro definition:
 * #define PI 3.14159
 *
 * Example usage:
 * double circumference = 2 * PI * radius;
*/

// ❌ I AM NOT DONE

#include <stdio.h>

// [TODO] DEFINE CONSTANTS LOWER, UPPER, AND STEP WITH APPROPRIATE VALUES.
#define LOWER // lower limit of the table
#define UPPER // upper limit of the table
#define STEP  // step size between consecutive temperatures
// END OF THE CONSTANTS

int main() {
	int fahr;

	// [TODO] REPLACE THE MAGIC NUMBERS WITH THE SYMBOLIC CONSTANTS.
	for (fahr = 0; fahr <= 300; fahr += 20) {
	// END OF THE REPLACEMENT
		printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	}

	return 0;
}

