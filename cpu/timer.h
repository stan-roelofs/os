#ifndef _CPU_TIMER_H
#define _CPU_TIMER_H

#include <types.h>

typedef void (*timer_handler_t)();
void init_timer(uint32_t frequency, timer_handler_t handler);

#endif