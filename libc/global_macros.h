
#ifndef __KERNEL_GLOBAL_MACROS_H__
#define __KERNEL_GLOBAL_MACROS_H__

// Random type
#define BYTE_LENGTH 8
#define FALSE 0
#define TRUE 1

// INTERRUPT GATE TYPE VALUE FOR GATE DESCRIPTOR

#define IDT_TASK_GATE 0x5
#define IDT_INTERRUPT_GATE_16 0x6
#define IDT_TRAP_GATE_16 0x7
#define IDT_INTERRUPT_GATE_32 0xE
#define IDT_TRAP_GATE_32 0xF


// CPU informations
#define CPU_FREQ_Hz 1193180  // 3791998 MHz but larger file cause crash (Need to debug)


#endif