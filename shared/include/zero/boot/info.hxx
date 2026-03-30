// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_BOOT_INFO_HXX
#define _ZERO_BOOT_INFO_HXX

#include "../types.hxx"

extern "C" struct Zr_BootInfoVideo
{
    zero::UWord vgaMode;
    zero::UWord width;
    zero::UWord height;
};

extern "C" struct Zr_BootInfo
{
    struct Zr_BootInfoVideo *video;
};

#endif
