//TEMP HALLOC

#include "halloc.h"

extern u32int end;
u32int placement_address = (u32int)&end;

u32int halloc_int(u32int sz, int align, u32int *phys)
{
    if (align == 1 && (placement_address & 0xFFFFF000) )
    {
        // Align the placement address;
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
        *phys = placement_address;
    u32int tmp = placement_address;
    placement_address += sz;
    return tmp;
}

u32int halloc_a(u32int sz)
{
    return halloc_int(sz, 1, 0);
}

u32int halloc_p(u32int sz, u32int *phys)
{
    return halloc_int(sz, 0, phys);
}

u32int halloc_ap(u32int sz, u32int *phys)
{
    return halloc_int(sz, 1, phys);
}

u32int halloc(u32int sz)
{
    return halloc_int(sz, 0, 0);
}
