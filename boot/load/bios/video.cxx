// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

__asm(".code16");

#include <zero/types.hxx>

namespace zero::boot::bios
{
    static UWord currentVideoMode_ = 0x03;

    void
    SetVideoMode(UWord mode)
    {
        __asm volatile("xorb %%ah, %%ah\n"
                       "movw %0, %%ax\n"
                       "int $0x10\n"
                       :
                       : "r"(mode)
                       : "ax", "ah");
        currentVideoMode_ = mode;
    }

    UWord
    GetVideoMode()
    {
        return currentVideoMode_;
    }
} // namespace zero::boot::bios
