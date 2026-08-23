//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      An implementation of video mode set  function
//

__asm(".code16");

#include <hlbvid.h>

void
HlbSetVideoMode(HLB_VIDEO_MODE NewVideoMode)
{
    __asm volatile("int $0x10\n" : : "a"(NewVideoMode));
}
