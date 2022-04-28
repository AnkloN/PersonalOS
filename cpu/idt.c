// Interrupt Descriptor Table
#include "idt.h"
#include "./../libc/util.h"

void set_idt_gate(int n, uint_32 handler){
    idt[n].low_offset = low_16b(handler);
    idt[n].high_offset = high_16b(handler);
    idt[n].always0 = 0; // why ??
    idt[n].selector = KERNEL_CS;
    idt[n].flags = 0x8E; // why ??
}


void set_idt(){
    idt_reg.base = (uint_32) &idt;
    idt_reg.limit = IDT_ENTRIES*sizeof(idt_gate_t) - 1;
    __asm__ __volatile__("lidtl (%0)"::"r"(&idt_reg)); // load idt to idt_reg
}
