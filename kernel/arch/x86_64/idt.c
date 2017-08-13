#include <k/idt.h>

void idt_set(uint8_t num, idt_gate_t base, uint16_t sel, uint8_t flags) {
    idt.entries[num].base_low = ((uintptr_t)base & 0xFFFF);
    idt.entries[num].base_high = ((uintptr_t)base >> 16) & 0xFFFF;
    idt.entries[num].sel = sel;
    idt.entries[num].zero = 0;
    idt.entries[num].flags = flags | 0x60;
}

void idt_init(void) {
    idt_pointer_t * idtp = &idt.pointer;
    idtp->limit = sizeof idt.entries - 1;
    idtp->base = (uintptr_t)&ENTRY(0);
    memset(&ENTRY(0), 0, sizeof idt.entries);

    idt_load((uintptr_t)idtp);
}
