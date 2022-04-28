// Interrupt Descriptor Table
#ifndef __INTERRUPT_DESCRIPTOR_TABLE_H__
#define __INTERRUPT_DESCRIPTOR_TABLE_H__
// #include<stdint.h>
#include "types.h"

#define KERNEL_CS 0x08 // kernel segment
#define IDT_ENTRIES 256


// Interrupt gate
typedef struct{
    uint_16 low_offset; // lower 16 bit
    uint_16 selector; // segment selector
    uchar_8 always0; // gate type
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" 
     * defines CPU privilate levels*/
    uchar_8 flags; 
    uint_16 high_offset;
}__attribute__((packed)) idt_gate_t;

// pointer to the interrupt handler
typedef struct {
    uint_16 limit;
    uint_32 base;
}__attribute__((packed))idt_register_t;

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;


void set_idt_gate(int n, uint_32 handler);
void set_idt();


#endif