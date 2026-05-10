// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_PRIMARY_PM_H
#define _VACUI_PRIMARY_PM_H

#include <stdint.h>

#define __pm [[gnu::section (".pm")]]

#define PM_GDT_COUNT 5

struct [[gnu::packed]] pm_gdt_entry {
        unsigned short limit_low;
        unsigned short base_low;
        unsigned char base_middle;
        unsigned char access;
        unsigned char granularity;
        unsigned char base_high;
};

struct [[gnu::packed]] pm_gdt_pointer {
        unsigned short limit;
        uintptr_t base;
};

__pm extern struct pm_gdt_entry pm_gdt_entries[PM_GDT_COUNT];
__pm extern struct pm_gdt_pointer pm_gdt_pointer_inst;

__pm void pm_set_gdt_entry (
    unsigned int base, unsigned int limit, unsigned char access,
    unsigned char flags
);

#endif
