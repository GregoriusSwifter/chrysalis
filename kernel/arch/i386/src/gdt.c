#include <freestanding.h>

#ifndef GDT_H
#include <gdt.h>
#endif

gdt_entry gdt_entries[6];

void gdt_set(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    /* Base Address */
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;
    /* Limits */
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0X0F;
    /* Granularity */
    gdt_entries[num].granularity |= (gran & 0xF0);
    /* Access flags */
    gdt_entries[num].access = access;
}
