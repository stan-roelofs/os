#ifndef _CPU_IDT_H
#define _CPU_IDT_H

#include <types.h>

#define KERNEL_CS 0x08

// Describes an interrupt gate
typedef struct
{
    uint16_t base_lo;       // Address to jump to when the interrupt fires (lower 16 bits)
    uint16_t selector;      // Segment selector
    uint8_t zero;
    uint8_t flags;          // Flags (bit 7 indicates the entry is present, bits 5-6 descriptor privilege level, bits 0-4 are fixed to 0b00110
    uint16_t base_hi;       // Address to jump to when the interrupt fires (upper 16 bits)
} __attribute__((packed)) idt_entry;

typedef struct
{
    uint16_t limit;
    uint32_t base;          // Address of the first idt_entry
} __attribute__((packed)) idt_ptr;

#define IDT_ENTRIES 256
extern idt_entry idt[IDT_ENTRIES];
extern idt_ptr idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif