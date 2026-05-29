// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      Bootloader startup code (BAL i386)

__asm(".code16gcc");

#include <gdt.h>
#include <hub.h>

// Description:
//
//      Global Descriptor Table instance with its entries.
//
// Notes:
//
//      - This GDT instance is only needed to handle transition between real
//      mode and protected mode.
//
//      - It doesn't contain TSS, only:
//              Null entry
//              Kernel mode code segment
//              Kernel mode data segment
//
//      - This GDT is overwritten by kernel's GDT later.
static ulong_t gdt_[3] = {};

// Description:
//
//      Initializes a temporary Global Descriptor Table
//      without loading it with lgdt.
static void gdt_init_()
{
    // Null entry
    gdt_[0] = gdt_make_entry(0, 0, 0);
    // Kernel mode code segment
    gdt_[1] = gdt_make_entry(0, 0xFFFFF, (0x9A << 8) | 0xC);
    // Kernel mode data segment
    gdt_[2] = gdt_make_entry(0, 0xFFFFF, (0x92 << 8) | 0xC);
}

[[noreturn]] void hub()
{
    gdt_init_();
    while (1)
        __asm volatile("hlt\n");
}
