#define ISR_H
#include <freestanding.h>

typedef struct {
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t int_num;
    uint32_t err_num;
    uint32_t eip;
    uint32_t cs;
    uint32_t cflags;
    uint32_t uesp;
    uint32_t ss;
} isr_registers;

typedef struct {
    void (*handler)();
    uint8_t index;
} isr_handle;

typedef enum {
    ISR_INT_DIVIDEBYZERO,
    ISR_INT_DEBUG,
    ISR_INT_NMI,
    ISR_INT_BREAKPOINT,
    ISR_INT_OVERFLOW,
    ISR_INT_OUTOFBOUNDS,
    ISR_INT_INVALIDOPCODE,
    ISR_INT_NOCOPROCESSOR,
    ISR_INT_DOUBLEFAULT,
    ISR_INT_SEGMENTOVERRUN,
    ISR_INT_BADTSS,
    ISR_INT_SEGMENTNOTPRESENT,
    ISR_INT_STACKFAULT,
    ISR_INT_PROTECTIONFAULT,
    ISR_INT_PAGEFAULT,
    ISR_INT_UNKNOWN,
    ISR_INT_COPROCESSORFAULT,
    ISR_INT_ALIGNMENTCHECK,
    ISR_INT_MACHINECHECK
} isr_int;

#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

extern isr_handle isr_handles[256];

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr127();

void isr_handler(__volatile__ isr_registers r);
