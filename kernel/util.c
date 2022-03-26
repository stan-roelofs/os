#include "util.h"

#include "types.h"

void memory_copy(void* source, void* dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *((char*)dest + i) = *((char*)source + i);
    }
}