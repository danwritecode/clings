#include <stdio.h>

int main()
{
    printf("hello world");
    int *ptr = NULL;  // Initialize a pointer to NULL
    int value = *ptr; // Dereference the NULL pointer, causing a segfault
    printf("%d\n", value);
    return 0;
}
