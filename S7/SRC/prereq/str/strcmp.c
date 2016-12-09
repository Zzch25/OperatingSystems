#include "string.h"

int strcmp(char *x, char *y)
{
      int i = 0;
	  
      for(; x[i] != '\0' && y[i] != '\0'; i++)
      {
		if(x[i] != y[i])
			return -1;
      }

      if(x[i] != '\0' || y[i] != '\0')
          return 1;
  
      return 0;
}