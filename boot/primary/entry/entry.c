// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Kernel entry function.

__asm(".code16gcc");

#include <bios/video.h>

[[noreturn]] void entry()
{
    bios_teletype_output('A', 1);
    while (true)
        __asm volatile("hlt");
}
