#include "string.h"

#include <types.h>

int strlen(const char* str)
{
    int i = 0;
    while (str[i] != '\0')
        ++i;

    return i;
}

char* string_reverse(char* str)
{
    const int length = strlen(str);
    for (int i = 0; i < length / 2; ++i)
    {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }

    return str;
}

char* int_to_ascii(int n, char* str)
{
    int i = 0;
    bool negative = n < 0;

    do {
        str[i++] = n % 10 + '0';
        n /= 10;
    } while (n > 0);

    if (negative)
        str[i++] = '-';

    str[i] = '\0';

    return string_reverse(str);
}