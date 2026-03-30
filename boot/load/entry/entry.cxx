// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

__asm(".code16");

#include <zero/bios/video.hxx>
#include <zero/types.hxx>

extern "C" void
Entry()
{
    using namespace zero::boot;
    bios::SetVideoMode(0x13);
    while (true)
    {
        __asm volatile("hlt\n" : : :);
    }
}
