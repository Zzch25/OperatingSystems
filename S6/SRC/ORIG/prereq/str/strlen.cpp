#include "string.h"

int strlen(const char *s)
{
	const char *str = s;
	for(; *str; str++);
	return(str - s);
}


