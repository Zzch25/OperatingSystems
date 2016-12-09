#include "string.h"

int strcmp(char *s1,char *s2)
{
  if(s1==NULL)
  {
    if(s2==NULL)
      return 0;
    return -1;
  }
  if(s2==NULL)
    return 1;

  for(;*s1,*s2;s1++,s2++)
    if(*s1!=*s2)
      return -1;

  if(*s1!='\0')
    return 1;
  if(*s2!='\0')
    return -1;
  
  return 0;
}