#include "prereq/tdef.h"
#include "prereq/str/string.h"
#include "prereq/mem/memm.h"

void terminal_init();
void kout(const char* data);
void kochr(char in);
void koint(s32int in);
void kohex(s32int in);