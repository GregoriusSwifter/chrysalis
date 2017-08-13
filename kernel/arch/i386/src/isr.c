#ifndef ISR_H
#include <isr.h>
#endif

isr_handle isr_handles[256];

void isr_handler(__volatile__ isr_registers r) {
    if (r.int_num >= IRQ0 && r.int_num <= IRQ15) {
        if (r.int_num >= 40) {
            outb(0xA0, 0x20);
        }
        outb(0x20, 0x20);
    }
    isr_handle *isr_h = &isr_handles[r.int_num];
    if (isr_h->handler) {
        isr_h->handler(r);
    }
}
