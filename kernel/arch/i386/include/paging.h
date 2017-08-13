#define PAGING_H

#include <freestanding.h>

extern uint32_t __attribute__((aligned(4096))) page_directory[1024];
extern uint32_t __attribute__((aligned(4096))) page_table_0[1024];

void static inline paging_set_get_cr0(uint32_t value) {
    __asm__ __volatile__ ("mov %%cr0, %%eax;"
                           "or %0, %%eax;"
                           "mov %%eax, %%cr0;"
                           :
                           : "r"(value)
                           : "eax", "cc" );
}

void static inline paging_set_get_cr3(void *ptr) {
    __asm__ __volatile__ ("mov %0, %%cr3;"
                           :
                           : "r"(ptr)
                           : "cc" );
}

void static inline paging_set_get_cr4(uint32_t value) {
    __asm__ __volatile__ ("mov %%cr4, %%eax;"
                           "or %0, %%eax;"
                           "mov %%eax, %%cr4;"
                           :
                           : "r"(value)
                           : "eax", "cc" );
}
