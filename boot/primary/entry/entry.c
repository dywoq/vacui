// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Kernel entry function.

__asm(".code16gcc");

[[noreturn]] void entry()
{
    while (true)
        __asm volatile("hlt");
}
