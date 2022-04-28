#include "timer.h"
#include "isr.h"
#include "./../drivers/screen.h"
#include "./../libc/util.h"
#include "./../libc/global_macros.h"

uint_32 tick = 0;
static void timer_callback(registers_t regs){
    char tick_ascii[256];
    tick++;
    int_to_ascii(tick, tick_ascii);
    kprint("tick : ");
    kprint(tick_ascii);
    kline_break();
}

void init_timer(uint_32 freq){
    register_interrupt_handler(IRQ0, timer_callback);
    uint_32 divisor = CPU_FREQ_Hz/freq;
    uchar_8 low = (uchar_8)(divisor && 0xFF);
    uchar_8 high = ( uchar_8)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
    
}