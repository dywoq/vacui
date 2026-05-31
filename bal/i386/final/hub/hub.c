/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Startup code of final bootloader stage
*/

#include <vqcmpext.h>
#include <vqtypes.h>

_SECTION(".start") _NORETURN void hub()
{
    while (1)
        __asm volatile("hlt\n");
}
