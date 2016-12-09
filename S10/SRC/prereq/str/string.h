#ifndef STRING_H
#define STRING_H

#include "../tdef.h"

int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strlen(const char *);

#endif