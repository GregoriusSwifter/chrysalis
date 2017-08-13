#define IDT_H
#include <freestanding.h>

typedef struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry;

typedef struct {
    uint16_t    limit;
    idt_entry   *base;
} __attribute__((packed)) idt_pointer;

extern idt_entry idt_entries[256];

static inline void idt_load(idt_entry *base, uint16_t size) {
    idt_pointer idt_ptr = { size, base };
    __asm__ __volatile__ ( "lidt %0" : : "m"(idt_ptr) );
}

void idt_set(uint8_t num, uintptr_t base, uint16_t sel, uint8_t flags);
