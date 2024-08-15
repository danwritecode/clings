/* 
 * So what is a practical application of all of this? 
 *
 * How about a program to convert from Fahrenheit to Celcius.
 *
 * The program below is not accurate enough, how can we fix that?
*/

// ❌ I AM NOT DONE


#include <assert.h>
#include <math.h>

#define EPSILON 0.000001

int main() {
	int fahrenheit = 100;
	int celcius = (5 / 9) * (fahrenheit - 32);

	// DO NOT CHANGE THIS
	assert(fabs(celcius - 37.777779) < EPSILON);
	return 0;
}
