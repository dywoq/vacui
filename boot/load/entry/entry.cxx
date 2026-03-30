// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

__asm(".code16");

#include <zero/types.hxx>

extern "C" void
Entry()
{
    while (true)
    {
        __asm volatile("hlt\n" : : :);
    }
}
