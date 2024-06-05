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
