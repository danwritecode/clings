// Welcome to clings!
// This first exercise is just to show you how things work.
// 
// There are two ways an exercise could be failing: 
// 1. Compilation Error
// 2. Runtime Error
//
// Your goal is to complete an exercise and get it to both compile and also to run with no errors
// while following the directions of the exercise. 
//
// Once there are no errors and you're ready to move on, delete the "I AM NOT DONE" line.


// ❌ I AM NOT DONE


#include <stdio.h>

int main()
{
    char msg[] = "\033[1;32m"
             "      _ _                 \n"
             "     | (_)                \n"
             "  ___| |_ _ __   __ _ ___ \n"
             " / __| | | '_ \\ / _` / __|\n"
             "| (__| | | | | | (_| \\__ \\\n"
             " \\___|_|_|_| |_|\\__, |___/\n"
             "                 __/ |    \n"
             "                |___/     \n"
             "\033[0m";

    printf("%s\n", msg);

    // Missing something here? What does the compiler say?
    printf("Welcome to clings! \n")

    // This is a segmentation fault
    // It's added to demonstrate a runtime failure
    // For now, just delete these lines to see a successful exercise completion
    int *ptr = NULL;
    *ptr = 42;

    return 0;
}
