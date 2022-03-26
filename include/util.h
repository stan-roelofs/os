#ifndef _UTIL_H
#define _UTIL_H

void memory_copy(void* source, void* dest, int nbytes);

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

#endif