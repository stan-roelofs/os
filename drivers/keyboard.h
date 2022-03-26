#ifndef _DRIVERS_KEYBOARD_H
#define _DRIVERS_KEYBOARD_H

#include <types.h>

typedef void (*keyboard_handler_t)(uint8_t scancode);
void init_keyboard(keyboard_handler_t handler);

#endif