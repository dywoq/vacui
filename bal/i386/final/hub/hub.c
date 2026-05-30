/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Startup code of final bootloader stage
*/

#include <vqcmpext.h>
#include <vqtypes.h>

_NORETURN void
hub()
{
    volatile ubyte_t *vram = (volatile ubyte_t *)0xb8000;
    vram[0 * 80 + 0]       = ' ';

    while (1)
        __asm volatile("hlt\n");
}
