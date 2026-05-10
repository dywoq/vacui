// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm (".code16gcc");

#include <stdint.h>
#include <vacui/primary/pm.h>

static char gdt_entries_top_ = 0;

void pm_set_gdt_entry (
    unsigned int base, unsigned int limit, unsigned char access,
    unsigned char flags
)
{
        pm_gdt_entries[gdt_entries_top_].limit_low = limit & 0xFFFF;
        pm_gdt_entries[gdt_entries_top_].base_low = base & 0xFFFF;
        pm_gdt_entries[gdt_entries_top_].base_middle = (base >> 16) & 0xFF;
        pm_gdt_entries[gdt_entries_top_].base_high = (base >> 24) & 0xFF;
        pm_gdt_entries[gdt_entries_top_].access = access;
        pm_gdt_entries[gdt_entries_top_].granularity =
            ((limit >> 16) & 0x0F) | ((flags & 0x0F) << 4);
        gdt_entries_top_++;
}
