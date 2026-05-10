// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/bootinfo.h>
#include <vacui/primary/bios.h>

struct boot_info hub_boot_info = {};

struct bios_dpa hub_kernel_dap = {
    .size = 16,
    .reserved = 0,
    .sections = 2,
    .offset = 0x1000,
    .segment = 0x0,
    .start = 2,
};
