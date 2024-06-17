/*
 * The provided file will not compile until the user fixes all mistakes.
 * (You can only delete/edit lines with // <-- Fix this line)
 */

// ❌ I AM NOT DONE

#include <stdio.h>

int main() {
    int lower = 0, upper; // <-- Fix this line 
    char c, line[1000]; 

    lower = 10;
    upper = 20;
    step = 2; // <-- Fix this line

    for (int i = lower; i <= upper; i += step) {
        printf("Value: %d\n", i);
    }

    float eps;
    const double e = 2.71828182845905;
    const char msg[] = "warning: ";

    eps = 1.0e-5; 

    e = 3.14; // <-- Fix this line

    printf("%s The value of e is: %f\n", msg, e);
    printf("Epsilon value is: %f\n", eps);

    return 0;
}
