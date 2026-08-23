//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      An implementation of video mode get function
//

__asm(".code16");

#include <hlbvid.h>
#include <vqdef.h>

HLB_VIDEO_MODE
HlbGetVideoMode()
{
    VQ_USHORT RetrievedVideoMode = 0;
    __asm volatile("int $0x10\n" : "=a"(RetrievedVideoMode) : "a"((0x0F << 8)));
    return (HLB_VIDEO_MODE)(RetrievedVideoMode & 0xFF);
}
