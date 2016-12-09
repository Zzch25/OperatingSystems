#ifndef SCREENOUT_H
#define SCREENOUT_H

#include "cdef.h"

void terminal_init();
void kout(const char* data);
void kochr(char in);
void koint(s32int in);
void kohex(s32int in);

#endif