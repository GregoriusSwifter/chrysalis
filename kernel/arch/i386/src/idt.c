#ifndef IDT_H
#include <idt.h>
#endif

idt_entry idt_entries[256];

void idt_set(uint8_t num, uintptr_t base, uint16_t sel, uint8_t flags) {
    idt_entries[num].base_low  = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].sel       = sel;
    idt_entries[num].zero      = 0;
    idt_entries[num].flags     = flags | 0x60;
}
