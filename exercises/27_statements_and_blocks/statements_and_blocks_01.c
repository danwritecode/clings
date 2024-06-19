/* 
 * Blocks in C are defined with the braces { }. Oftentimes these braces are required in things like for loops, but they are
 * also used to put things into their own "scope".
 *
 * Take a look at the program below and figure out why this program is not compiling.
*/

// ❌ I AM NOT DONE

#include <assert.h>
#include <stdio.h>

int main() {
	int sum = 0;

	// do not get rid fo the braces
	{
		// could these move somewhere else?
		int a = 1;
		int b = 2;
		int c = 3;
	}
	    
	// could this move somewhere else?
	sum = a + b + c;


	// do not change this
	printf("sum: %i \n", sum);
	assert(sum == 6);
	return 0;
}
