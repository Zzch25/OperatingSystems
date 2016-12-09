#include "memm.h"

//specific rewrite.. if fail otherwise
void memset(void *dest, u8int val, u32int len)
{
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
