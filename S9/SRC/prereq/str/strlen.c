#include "string.h"

int strlen(const char *s)
{
	if(s == NULL)
		return -1;
	
	const char *str = s;
	for(; *str; str++);
	return(str - s);
}