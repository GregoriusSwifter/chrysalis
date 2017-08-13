#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <freestanding.h>

void terminal_initialize(void);
void terminal_write(char c);
void terminal_setcolor(uint8_t color);

#endif
