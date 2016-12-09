#ifndef HALLOC_H
#define HALLOC_H

#include "../prereq/str/string.h"
#include "../prereq/mem/memm.h"
#include "../prereq/tdef.h"

//alloc and allign
u32int halloc_int(u32int sz, int align, u32int *phys);

u32int halloc_a(u32int sz);

//returns phys
u32int halloc_p(u32int sz, u32int *phys);

//returns phys of mem alligned
u32int halloc_ap(u32int sz, u32int *phys);

u32int halloc(u32int sz);

#endif