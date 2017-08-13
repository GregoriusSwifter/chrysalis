#if !(__STDC_HOSTED__ == 0)
#error "This kernel expects a non-hosted compiler"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include <k/main.h>
#include <k/ssp.h>
#include <k/tty.h>

#include <stdio.h>
#include <string.h>

//#ifndef DESCRIPTOR_TABLES_H
//#include "descriptor_tables.h"
//#endif

//#ifndef TIMER_H
//#include "timer.h"
//#endif

//#ifndef MEM_H
//#include "mem.h"
//#endif

/* The attribute of an character. */
#define ATTRIBUTE 7

/* Check if the bit BIT in FLAGS is set. */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void k_main() {
    terminal_initialize();
    printf("OK\n");
    //idt_install();      /* IDT */
    //isrs_install();     /* Interrupt service requests */
    //irq_install();      /* Hardware interrupt requests */

    //kmeminit();
    //monitor_clear();
    //initialize_paging();
    //monitor_write((uint8_t *));
    printf("Hello, world!\n");

    /*
    uintptr_t *ptr = (uintptr_t *)0xA0000000;
    printf((uint8_t*)"herp derp %s", *ptr);
    return;
    */
}
