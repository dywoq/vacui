// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Kernel entry function.

__asm(".code16gcc");

#include <base/print.h>

[[noreturn]] void entry()
{
    base_print_raw("| Boot Primary stage is started\n\r");
    while (true)
        __asm volatile("hlt");
}
