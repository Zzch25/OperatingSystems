#ifndef MONITOR_H
#define MONITOR_H

#include "cdef.h"

// Write a single character out to the screen.
void monitor_put(char c);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

// Output a hex value to the monitor.
void monitor_write_hex(u32int n);

// Output a decimal value to the monitor.
void monitor_write_dec(u32int n);

#endif // MONITOR_H
