#define STRING_H

#include <freestanding.h>

int memcmp(void const *, void const *, size_t);
void* memcpy(void* __restrict, void const * __restrict, size_t);
void* memmove(void*, void const *, size_t);
void* memset(void*, int, size_t);
size_t strlen(char const *);
int strcmp(char const *s1, char const *s2);
