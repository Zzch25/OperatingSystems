#include "string.h"

//Note: nullT != \0
char *strcpy(char *dest, const char *src)
{
    do
      *dest++ = *src++;
    while (*src != 0);
}