#include "string.h"

//To End of dst
//Note: nullT != \0
char *strcat(char *dest, const char *src)
{
    while (*dest != 0)
        *dest = *dest++;
    do
        *dest++ = *src++;
    while (*src != 0);
    return dest;
}
