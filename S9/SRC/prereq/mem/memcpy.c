#include "memm.h"

//specific rewrite.. if fail otherwise
void memcpy(u8int *dest, const u8int *src, u32int len)
{
    const u8int *stemp = (const u8int *)src;
    u8int *dtemp = (u8int *)dest;
    for(; len != 0; len--) *dtemp++ = *stemp++;
}
