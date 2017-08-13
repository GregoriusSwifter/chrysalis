#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <freestanding.h>

#define EOF (-1)

void print(char const * data, uint32_t length);
int printf(char const * __restrict, ...);

#endif
