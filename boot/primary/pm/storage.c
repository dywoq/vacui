// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <stdint.h>
#include <vacui/primary/pm.h>

struct pm_gdt_entry pm_gdt_entries[PM_GDT_COUNT] = {};

struct pm_gdt_pointer pm_gdt_pointer_inst = {
    .limit = sizeof (pm_gdt_entries) - 1,
    .base = (uintptr_t)&pm_gdt_entries,
};
