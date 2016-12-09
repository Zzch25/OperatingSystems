#include "../sysdef/cdef.h"

void outb(u16int port, u8int value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
    u8int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16int inw(u16int port)
{
    u16int ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void* memcpy(void* dstptr, const void* srcptr, size_t size)
{
	size_t i;
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for ( i = 0; i < size; i++ )
		dst[i] = src[i];
	return dstptr;
}

void* memset(void* bufptr, int value, size_t size)
{
	size_t i;
	unsigned char* buf = (unsigned char*) bufptr;
	for (i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

int strcmp(char *s1, char *s2)
{
	for(;*s1,*s2;s1++,s2++)
		if(*s1!=*s2)
			return -1;

	if(*s1!='\0')
		return 1;
	if(*s2!='\0')
		return -1;
  
	return 0;
}

char *strcpy(char *s1, const char *s2)
{
    char *temp = s1;
	while(*s1++ = *s2++);
	
	return temp;
}

char *strcat(char *s1, const char *s2)
{
    for(;*s1;s1++);
	for(;*s2;s1++,s2++) *s1=*s2;	
	*s1=0;
	
    return s1;
}

size_t strlen(const char* string)
{
	size_t result = 0;
	while (string[result++]);
	
	return result;
}

extern void panic(const char *message, const char *file, u32int line)
{
    asm volatile("cli");
	
    kout("PANIC(");
    kout(message);
    kout(") at ");
    kout(file);
    kout(":");
    koint(line);
    kout("\n");
    for(;;);
}

extern void panic_assert(const char *file, u32int line, const char *desc)
{
    asm volatile("cli");

    kout("ASSERTION-FAILED(");
    kout(desc);
    kout(") at ");
    kout(file);
    kout(":");
    koint(line);
    kout("\n");
    for(;;);
}
