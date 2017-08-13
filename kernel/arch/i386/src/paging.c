#ifndef PAGING_H
#include <paging.h>
#endif

#include <stdio.h>

uint32_t __attribute__((aligned(4096))) page_directory[1024];
uint32_t __attribute__((aligned(4096))) page_table_0[1024]; // attributes: supervisor level, read/write, present.
