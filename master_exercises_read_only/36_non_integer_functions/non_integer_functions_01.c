/*
 * Exercise: Implementing Heron's formula for triangle area
 * 
 * In this exercise, you'll create a function called triangle_area that 
 * calculates the area of a triangle given the lengths of its three sides
 * using Heron's formula.
 * 
 * Heron's formula: Area = sqrt(s * (s - a) * (s - b) * (s - c))
 * where s = (a + b + c) / 2 
 * and a, b, c are the lengths of the triangle's sides.
 * 
 * Your tasks:
 * 1. Complete the triangle_area function to return the correct area.
 * 2. Use the provided sqrt function for square root calculation.
 * 3. Handle invalid triangles by returning -1.0 for any errors.
 * 4. Make sure the assert statements pass after your implementation.
 * 
 * Tips:
 * - Check if the given side lengths can form a valid triangle.
 */

// ❌ I AM NOT DONE

#include <math.h>
#include <assert.h>
#include <stdio.h>

// You can use this tolerance for floating-point comparisons
#define EPSILON 1e-6

// Implement this function
// TODO: correct return type
triangle_area(double a, double b, double c) {
	// TODO: Check if all sides are positive
	if () {
		return ; 
	}

	// TODO: Check Triangle Inequality Theorem
	if () {
		return ; 
	}

	// TODO: Calculate area

	return
}

// Helper function for comparing floating-point numbers
int double_equals(double a, double b) {
    return fabs(a - b) < EPSILON;
}

int main(void) {

    // Test cases
    assert(double_equals(triangle_area(3, 4, 5), 6.0));
    assert(double_equals(triangle_area(5, 12, 13), 30.0));
    assert(double_equals(triangle_area(2, 2, 2), 1.732051));
    assert(double_equals(triangle_area(1, 1, 1.41), 0.499991));
    
    // Error cases
    assert(double_equals(triangle_area(1, 1, 3), -1.0));  // Invalid triangle
    assert(double_equals(triangle_area(0, 4, 5), -1.0));  // Side length can't be 0
    assert(double_equals(triangle_area(-1, 4, 5), -1.0)); // Side length can't be negative

    printf("All tests passed!\n");
    return 0;
}
