#include "isr.h"
#include "idt.h"
#include "./../drivers/screen.h"
#include "./../libc/util.h"

// Lets define an array of error message associated with interrupt
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",

    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",

    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
isr_t interrupt_handlers[256];


void isr_install(){
    // it is tempting to do this in loop but dont
    // we will need thier address later
    set_idt_gate(0, (uint_32)isr0);
    set_idt_gate(1, (uint_32)isr1);
    set_idt_gate(2, (uint_32)isr2);
    set_idt_gate(3, (uint_32)isr3);
    set_idt_gate(4, (uint_32)isr4);
    set_idt_gate(5, (uint_32)isr5);
    set_idt_gate(6, (uint_32)isr6);
    set_idt_gate(7, (uint_32)isr7);
    set_idt_gate(8, (uint_32)isr8);
    set_idt_gate(9, (uint_32)isr9);
    set_idt_gate(10, (uint_32)isr10);
    set_idt_gate(11, (uint_32)isr11);
    set_idt_gate(12, (uint_32)isr12);
    set_idt_gate(13, (uint_32)isr13);
    set_idt_gate(14, (uint_32)isr14);
    set_idt_gate(15, (uint_32)isr15);
    set_idt_gate(16, (uint_32)isr16);
    set_idt_gate(17, (uint_32)isr17);
    set_idt_gate(18, (uint_32)isr18);
    set_idt_gate(19, (uint_32)isr19);
    set_idt_gate(20, (uint_32)isr20);
    set_idt_gate(21, (uint_32)isr21);
    set_idt_gate(22, (uint_32)isr22);
    set_idt_gate(23, (uint_32)isr23);
    set_idt_gate(24, (uint_32)isr24);
    set_idt_gate(25, (uint_32)isr25);
    set_idt_gate(26, (uint_32)isr26);
    set_idt_gate(27, (uint_32)isr27);
    set_idt_gate(28, (uint_32)isr28);
    set_idt_gate(29, (uint_32)isr29);
    set_idt_gate(30, (uint_32)isr30);
    set_idt_gate(31, (uint_32)isr31);
    // TODO: come back later when you could debug and make it more readable
    // Remap the PIC
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0); 

    // Install the IRQs
    set_idt_gate(32, (uint_32)irq0);
    set_idt_gate(33, (uint_32)irq1);
    set_idt_gate(34, (uint_32)irq2);
    set_idt_gate(35, (uint_32)irq3);
    set_idt_gate(36, (uint_32)irq4);
    set_idt_gate(37, (uint_32)irq5);
    set_idt_gate(38, (uint_32)irq6);
    set_idt_gate(39, (uint_32)irq7);
    set_idt_gate(40, (uint_32)irq8);
    set_idt_gate(41, (uint_32)irq9);
    set_idt_gate(42, (uint_32)irq10);
    set_idt_gate(43, (uint_32)irq11);
    set_idt_gate(44, (uint_32)irq12);
    set_idt_gate(45, (uint_32)irq13);
    set_idt_gate(46, (uint_32)irq14);
    set_idt_gate(47, (uint_32)irq15);

    set_idt(); 
}

void register_interrupt_handler(uchar_8 n, isr_t handler){
    interrupt_handlers[n]=handler;
}

void isr_handler(registers_t reg){
    kprint("received interrupt: ");
    char s[3];
    int_to_ascii(reg.interrupt_no,s);
    kprint(s);
    kprint("  ");
    kprint(exception_messages[reg.interrupt_no]);
    kline_break();
}




void irq_handler(registers_t reg){
    // Send end of interrupt EOI to PIC so that it would send next interrupt
    if(reg.interrupt_no >=40){
        port_byte_out(SLAVE_COMMAND_PIC,0x20);
    }
    port_byte_out(MASTER_COMMAND_PIC,0x20);

    if(interrupt_handlers[reg.interrupt_no]!=0){
        isr_t handler = interrupt_handlers[reg.interrupt_no]; // get the function pointer
        handler(reg); // call the function
    }
}