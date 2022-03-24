#include "util.h"

#include "types.h"

void memory_copy(void* source, void* dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *((char*)dest + i) = *((char*)source + i);
    }
}

void int_to_ascii(int n, char* str)
{
    int i = 0;
    bool negative = n < 0;

    do {
        str[i++] = n % 10 + '0';
        n /= 10;
    } while ((n / 10) > 0);

    if (negative)
        str[i++] = '-';

    str[i] = '\0';

    for (int j = 0; j < (i - 1) / 2; ++j) 
    {
        char tmp = str[j];
        str[j] = str[i-1-j];
        str[i-1-j] = tmp;
    } // TODO is this correct?
}