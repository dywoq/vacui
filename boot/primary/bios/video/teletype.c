// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// An implementation of teletype functions

__asm(".code16gcc");

#include <vacui/types.h>

void bios_teletype_output(
    vac_ubyte_t ch,
    vac_ubyte_t page
)
{
    __asm volatile("int $0x10\n"
                   :
                   : "a"((0x0E << 8) | ch), "b"((page << 8))
                   : "cc", "memory");
}
