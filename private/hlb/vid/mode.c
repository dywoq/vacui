//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      Implementation of video mode management functions
//

__asm(".code16");

#include <hlbvid.h>

void
HlbSetVideoMode(HLB_VIDEO_MODE NewVideoMode)
{
    __asm volatile("int $0x10\n" : : "a"(NewVideoMode));
}

HLB_VIDEO_MODE
HlbGetVideoMode()
{
    HLB_VIDEO_MODE RetrievedVideoMode;
    __asm volatile("int $0x10" : "=a"(RetrievedVideoMode));
    return RetrievedVideoMode & 0xFF;
}
