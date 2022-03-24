#include "idt.h"

#include <util.h>

idt_entry idt[IDT_ENTRIES];
idt_ptr idt_reg;

void set_idt_gate(int n, uint32_t handler) {
    idt[n].base_lo = low_16(handler);
    idt[n].selector = KERNEL_CS;
    idt[n].zero = 0;
    idt[n].flags = 0x8E; 
    idt[n].base_hi = high_16(handler);
}

void set_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_entry) - 1;
    
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}