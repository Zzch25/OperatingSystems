#include "string.h"

size_t strlen(const char *s)
{
	const char *str = s;
	for(; *str; str++);
	return(str - s);
}
