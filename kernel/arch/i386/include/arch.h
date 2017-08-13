#define ARCH_H

#define KERNEL_VIRTUAL_BASE (0xE0000000)

#include <freestanding.h>

#ifndef MULTIBOOT_H
#include <multiboot.h>
#endif

static inline void cli(void) {
    __asm__ __volatile__("cli");
}

static inline void sti(void) {
    __asm__ __volatile__("sti");
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void arch_init(multiboot_info* mbt, unsigned int magic);
