#include "string.h"

char *my_strcat(char *s1,char *s2)
{
	if(s1==NULL || s2==NULL)
		return s1;
	
	int i,j;

	for(i=0; s1[i]!='\0';i++);
	for(j=0; s2[j]!='\0';j++,i++)
		s1[i]=s2[j];
	s1[i]='\0';
		
	return s1;
}