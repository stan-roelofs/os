#include "keyboard.h"

#include "ports.h"
#include "../cpu/isr.h"

keyboard_handler_t keyboard_handler = NULL;

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    keyboard_handler(scancode);
}

void init_keyboard(keyboard_handler_t handler) {
   register_interrupt_handler(IRQ1, keyboard_callback);
   keyboard_handler = handler;
}