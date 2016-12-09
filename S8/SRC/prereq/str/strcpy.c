#include "string.h"

char *my_strcpy(char *s1,char *s2)
{	
  if(s1 == NULL || s2 == NULL)
    return s1;

  char *temp = s1;
  while(*s1++ = *s2++);
  return temp;
}
