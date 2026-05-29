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
static ulong_t gdt_[3] = {0};

static struct [[gnu::packed]] {
    ushort_t limit;
    uint_t base;
} gdt_ptr_ = {0};

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

// Description:
//
//      Loads the Global Descriptor Table pointer into GDT register.
static void gdt_load_()
{
    gdt_ptr_.limit = sizeof(gdt_) - 1;
    gdt_ptr_.base = (ulong_t)gdt_;
    __asm volatile("lgdt %0" : : "m"(gdt_) : "cc", "memory");
}

[[noreturn]] void hub()
{
    gdt_init_();
    gdt_load_();
    while (1)
        __asm volatile("hlt\n");
}
