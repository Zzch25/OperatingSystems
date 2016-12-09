#include "../tdef.h"

void memset(void *dest, u8int val, u32int len);
void memcpy(void *dest, const void *src, u32int len);

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);