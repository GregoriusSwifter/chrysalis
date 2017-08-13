#ifndef ARCH_H
#include <arch.h>
#endif

#ifndef GDT_H
#include <gdt.h>
#endif

#ifndef TSS_H
#include <tss.h>
#endif

#ifndef ISR_H
#include <isr.h>
#endif

#ifndef IDT_H
#include <idt.h>
#endif

#ifndef PAGING_H
#include <paging.h>
#endif

#ifndef ELF_H
#include <elf.h>
#endif

#include <string.h>

void arch_init(multiboot_info* mbt, unsigned int magic) {
    uint16_t i;

    if (magic != 0x1BADB002) {
        // Something went not according to specs. Print an error
        // message and halt, but do *not* rely on the multiboot
        // data structure.
        //printf("Bad magic: 0x%x\n", MB_MAGIC_CMP);
        __asm__ __volatile__("jmp halt;");
    }
    cli();

    gdt_set(0, 0, 0, 0, 0);                // NULL segment
    gdt_set(1, 0, 0xFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set(2, 0, 0xFFFFF, 0x92, 0xCF); // Data segment
    gdt_set(3, 0, 0xFFFFF, 0xFA, 0xCF); // User code
    gdt_set(4, 0, 0xFFFFF, 0xF2, 0xCF); // User data
    gdt_set(5, (uint32_t)&tss, sizeof(tss), 0xE9, 0x00);
    tss_set(0x10, 0x0);

    // gdt load and flush
    __asm__ __volatile__("lgdt (%0);" : : "r" (&gdt_entries[0]));
    __asm__ __volatile__("movl %0, %%ds;"
                        "movl %0, %%es;"
                        "movl %0, %%fs;"
                        "movl %0, %%ss;"
                        "ljmp $0x08, $.gdt_flush_end;"
                        ".gdt_flush_end:"
                        : : "r" (0x10));


    memset(&idt_entries[0], 0, sizeof(idt_entry) * 256);

    // tss flush
    __asm__ __volatile__("ltr %w0;" : : "r" ( 0x2B ));

    // IDT init
    idt_set(0, (uintptr_t)&isr0,  0x08, 0x8E);
    idt_set(1, (uintptr_t)&isr1,  0x08, 0x8E);
    idt_set(2, (uintptr_t)&isr2,  0x08, 0x8E);
    idt_set(3, (uintptr_t)&isr3,  0x08, 0x8E);
    idt_set(4, (uintptr_t)&isr4,  0x08, 0x8E);
    idt_set(5, (uintptr_t)&isr5,  0x08, 0x8E);
    idt_set(6, (uintptr_t)&isr6,  0x08, 0x8E);
    idt_set(7, (uintptr_t)&isr7,  0x08, 0x8E);
    idt_set(8, (uintptr_t)&isr8,  0x08, 0x8E);
    idt_set(9, (uintptr_t)&isr9,  0x08, 0x8E);
    idt_set(10, (uintptr_t)&isr10, 0x08, 0x8E);
    idt_set(11, (uintptr_t)&isr11, 0x08, 0x8E);
    idt_set(12, (uintptr_t)&isr12, 0x08, 0x8E);
    idt_set(13, (uintptr_t)&isr13, 0x08, 0x8E);
    idt_set(14, (uintptr_t)&isr14, 0x08, 0x8E);
    idt_set(15, (uintptr_t)&isr15, 0x08, 0x8E);
    idt_set(16, (uintptr_t)&isr16, 0x08, 0x8E);
    idt_set(17, (uintptr_t)&isr17, 0x08, 0x8E);
    idt_set(18, (uintptr_t)&isr18, 0x08, 0x8E);
    idt_set(19, (uintptr_t)&isr19, 0x08, 0x8E);
    idt_set(20, (uintptr_t)&isr20, 0x08, 0x8E);
    idt_set(21, (uintptr_t)&isr21, 0x08, 0x8E);
    idt_set(22, (uintptr_t)&isr22, 0x08, 0x8E);
    idt_set(23, (uintptr_t)&isr23, 0x08, 0x8E);
    idt_set(24, (uintptr_t)&isr24, 0x08, 0x8E);
    idt_set(25, (uintptr_t)&isr25, 0x08, 0x8E);
    idt_set(26, (uintptr_t)&isr26, 0x08, 0x8E);
    idt_set(27, (uintptr_t)&isr27, 0x08, 0x8E);
    idt_set(28, (uintptr_t)&isr28, 0x08, 0x8E);
    idt_set(29, (uintptr_t)&isr29, 0x08, 0x8E);
    idt_set(30, (uintptr_t)&isr30, 0x08, 0x8E);
    idt_set(31, (uintptr_t)&isr31, 0x08, 0x8E);
    idt_set(127, (uintptr_t)&isr127, 0x08, 0x8E);

    idt_load(&idt_entries[0], (sizeof(idt_entry)*256)-1);

    // paging init
    for(i=0; i<1024; ++i) {
        page_directory[i] = 0x00000002;
        page_table_0[i] = (i * 0x1000) | 3;
    }
    page_directory[0] = ((uint32_t)page_table_0) | 3;

    // Load cr3 with page_directory address
    paging_set_get_cr3((&page_directory)-KERNEL_VIRTUAL_BASE);

    // Enable 4MB pages
    paging_set_get_cr4(0x00000010);

    // Enable paging on cr0
    paging_set_get_cr0(0x80000000);

    elf_parse_kernel(mbt, NULL);

    sti();
}
