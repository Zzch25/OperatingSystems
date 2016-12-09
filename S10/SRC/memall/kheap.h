#ifndef KHEAP_H
#define KHEAP_H

#include "../prereq/str/string.h"
#include "../prereq/mem/memm.h"
#include "../prereq/tdef.h"
#include "oarray.h"

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

#define HEAP_INDEX_SIZE   0x20000
#define HEAP_MAGIC        0x123890AB
#define HEAP_MIN_SIZE     0x70000

//hole/block info
typedef struct
{
    u32int magic;
    u8int is_hole;
    u32int size;
} header_t;

typedef struct
{
    u32int magic;
    header_t *header;
} footer_t;

typedef struct
{
    ordered_array_t index;
    u32int start_address;
    u32int end_address;
    u32int max_address;
    u8int supervisor;
    u8int readonly;
} heap_t;

//create new
heap_t *create_heap(u32int start, u32int end, u32int max, u8int supervisor, u8int readonly);

//contiguous
void *alloc(u32int size, u8int page_align, heap_t *heap);

void free(void *p, heap_t *heap);

u32int kmalloc_int(u32int sz, int align, u32int *phys);

//page alligned & int
u32int kmalloc_a(u32int sz);

//int & returns allocated pos via phys
u32int kmalloc_p(u32int sz, u32int *phys);

//page allingned & int & returns allocated pos via phys
u32int kmalloc_ap(u32int sz, u32int *phys);

u32int kmalloc(u32int sz);

void kfree(void *p);

#endif