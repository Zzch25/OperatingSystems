#ifndef INITRD_H
#define INITRD_H

#include "../prereq/str/string.h"
#include "../prereq/mem/memm.h"
#include "../prereq/tdef.h"
#include "../memall/kheap.h"
#include "fs.h"

typedef struct
{
    u32int nfiles; //# files
} initrd_header_t;

typedef struct
{
    u8int magic;     
    s8int name[64];  
    u32int offset;   //from initrd start
    u32int length;   
} initrd_file_header_t;

// Init ramdisk, passed the address  multiboot module, returns completed fs node
fs_node_t *initialise_initrd(u32int location);

#endif
