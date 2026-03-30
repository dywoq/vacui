// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

__asm(".code16");

#include <zero/types.hxx>

namespace zero::boot::bios
{
    void
    SetVideoMode(UWord mode)
    {
        __asm volatile("movw %0, %%ax\n"
                       "int $0x10\n"
                       :
                       : "r"(mode)
                       : "ax");
    }
} // namespace zero::boot::bios
