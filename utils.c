#include <time.h>

void delay(int seconds) {
    int m_secs = 1000000 * seconds;
    clock_t start_time = clock();

    while (clock() < start_time + m_secs) {};
} 
