#include <freestanding.h>

#ifndef TSS_H
#include <tss.h>
#endif

#ifndef GDT_H
#include <gdt.h>
#endif

tss_entry tss;

void tss_set(uint16_t ss0, uint32_t esp0) {
    tss.ss0 = ss0;
    tss.esp0 = esp0;
    tss.cs = 0x0b;
    tss.ss = 0x13;
    tss.ds = 0x13;
    tss.es = 0x13;
    tss.fs = 0x13;
    tss.gs = 0x13;

    tss.iomap_base = sizeof(tss);
}

void tss_set_kernel_stack(uintptr_t stack) {
    tss.esp0 = stack;
}
