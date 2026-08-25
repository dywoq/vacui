//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      Video mode management implementation
//

__asm(".code16gcc");

#include <hlbvid.h>

void
HlbSetVideoMode(HLB_VIDEO_MODE VideoMode)
{
    __asm volatile("int $0x10\n" : : "a"((0x0E << 8) | VideoMode));
}
