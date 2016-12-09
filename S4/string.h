#ifndef __STRING_H
#define __STRING_H

#define NULL 0
#define size_t unsigned long

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memsetw(void *s, int c, size_t n);
size_t strlen(const char *);

#endif
