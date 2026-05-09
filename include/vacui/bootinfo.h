// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_BOOTINFO_H
#define _VACUI_BOOTINFO_H

enum boot_kernel_mode : unsigned char {
        BOOT_KERNEL_RECOVERY,
        BOOT_KERNEL_NORMAL,
};

struct boot_info {
        enum boot_kernel_mode kernel_mode;
};

#endif
