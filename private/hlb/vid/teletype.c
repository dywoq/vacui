//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      Implementation of video teletype functionality
//

__asm(".code16gcc");

#include <hlbvid.h>

void
HlbVideoTeletypeOutput(
    VQ_ASCIICHAR Character,
    VQ_UBYTE     PageNumber
)
{
    __asm volatile("int $0x10\n"
                   :
                   : "a"((0x0E << 8) | Character), "b"(PageNumber << 8));
}
