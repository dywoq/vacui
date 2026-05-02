// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Kernel entry function.

__asm(".code16gcc");

#include <base/print.h>
#include <debug/debug.h>

[[noreturn]] void entry()
{
    base_print_raw("| vqboot_primary is started\n\r");
    debug_raw("NON-OPTIMIZED BUILD OF vqboot_primary\n\r");

    debug_raw("HALTING\n\r");
    while (true)
        __asm volatile("hlt");
}
