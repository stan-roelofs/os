#include "timer.h"

#include <util.h>

#include "../drivers/ports.h"

#include "isr.h"

timer_handler_t timer_handler = NULL;

static void timer_callback(registers_t regs) {
    timer_handler();
}

void init_timer(uint32_t frequency, timer_handler_t handler) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    uint32_t divisor = 1193180 / frequency;
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
    /* Send the command */
    port_byte_out(0x43, 0x36); /* Command port */
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}