/*
 * Fix the program to handle type conversions correctly
 * 
 * In this exercise, you will correct the type conversion issues in the given program.
 * The program performs arithmetic operations involving integers, floats, and doubles.
 * Your task is to ensure that the calculations are correct and the results match the expected values.
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// ❌ I AM NOT DONE

int main() {

    int i1 = 1;
    int i2 = 3;

    int a;
    float b;
    double c;

    a = i1 / i2;
    b = i1 / (i2 + ); // <-- Fix here (b = 0.25)
    c = i1 / i2; // <-- Fix here (c = 0.333333)

    printf("a = %d, b = %f, c = %lf\n", a, b, c);

	// DO NOT CHANGE
	double tolerance = 0.000001;
    assert(a == 0);
    assert((b - 0.25) < tolerance);
    assert((c - 0.333333) < tolerance);

    printf("All tests passed.\n");
    return 0;
}
