// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <gdt.h>
#include <vqtypes.h>

GDTAPI ulong_t gdt_make_entry(
    uint_t base,
    uint_t limit,
    ushort_t flag
)
{
    // Null entry skip
    if (base == 0 && limit == 0 && flag == 0) {
        return 0;
    }
    ulong_t entry = 0;
    entry = limit & 0x00F0000;
    entry |= (flag << 8) & 0x00F0FF00;
    entry |= (base >> 16) & 0x000000FF;
    entry |= base & 0xFF000000;
    entry <<= 32;
    entry |= base << 16;
    entry |= limit & 0x0000FFFF;
    return entry;
}
