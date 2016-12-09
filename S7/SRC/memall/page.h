#ifndef PAGE_H
#define PAGE_H

#include "../prereq/str/string.h"
#include "../prereq/mem/memm.h"
#include "../prereq/tdef.h"
#include "panic.h"
#include "../busopetc/isr.h"

typedef struct page
{
    u32int present    : 1;   // Page present in memory
    u32int rw         : 1;   // Read-only if clear, readwrite if set
    u32int user       : 1;   // Supervisor if clear
    u32int accessed   : 1;   // Page access since refresh?
    u32int dirty      : 1;   // Page write since refresh?
    u32int unused     : 7;   // Amalgamation of unused and reserved bits
    u32int frame      : 20;  // Frame address s-12
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    //->pagetables
    page_table_t *tables[1024];
    //->page tables->physical
    u32int tablesPhysical[1024];

    //phys address tablesPhysical
    u32int physicalAddr;
} page_directory_t;

void initialise_paging();

//directory->c3
void switch_page_directory(page_directory_t *new);

//find or make page
page_t *get_page(u32int address, int make, page_directory_t *dir);

//handler
void page_fault(registers_t regs);

#endif