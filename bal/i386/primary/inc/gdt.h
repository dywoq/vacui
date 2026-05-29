// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      Global Descriptor Table functionality

#ifndef _GDT_H
#define _GDT_H

#include <vqtypes.h>

#define GDTAPI [[gnu::section(".gdt")]]

// Description:
//
//      Transforms the given parameters into one unified 64-bit address,
//      which is usable in Global Descriptor Table.
//
// Parameters:
//
//      - base: Address where the entry begins.
//      - limit: Maximum addressable unit. It's 20-bit value only, despite its
//       type having 32-bits.
//      - flag: Access Byte (8 bits) and Flags (3 bits). Since there's no
//      explicit flag for Access Byte, you must combine Access Byte and Flags
//      using bitwise OR:
//
//          flag = (Access Byte << 8) | Flags
GDTAPI ulong_t
gdt_make_entry(
    uint_t base,
    uint_t limit,
    ushort_t flag
);

#endif
