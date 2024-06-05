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
    printf("Welcome to clings! \n");

    return 0;
}
