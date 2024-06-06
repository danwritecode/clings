/* 
 * Arithmetic in C is pretty straightforward, though there are some gotchas. 
 *
 * If you use integers for division for example, you may lose precision in the output.
 *
 * The program below is using integers and is thus failing the assertion for a certain level of precision. 
 *
 * Make changes to the program so that precision is not lost.
*/

// ❌ I AM NOT DONE


#include <assert.h>
#include <math.h>

#define EPSILON 0.000001

int main() {
	int x = 100.0;
	int y = 9.0;
	int z = x / y;

	// DO NOT CHANGE THIS
	assert(fabs(z - 11.111111) < EPSILON);
	return 0;
}
