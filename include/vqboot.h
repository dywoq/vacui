/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui
*/

#ifndef _VQBOOT_H
#define _VQBOOT_H

#include "vqtypes.h"

/*
 * The reason of adding static assert:
 * - The primary bootloader defines boot information struct fields
 * as DWORD pointers (boot/primary/boot_info.S):
 *      boot_info:
            dd boot_video_mode
            ; ...
 * - The kernel is 32-bit.
 * - The memory layout must match.
 */
static_assert(sizeof(void *) == 4, "size of pointer must be 4 bytes");

enum boot_kernel_mode : ubyte_t {
    BOOT_KERNEL_NORMAL = 0,
    BOOT_KERNEL_RECOVERY,
};

struct boot_kernel_mode_info {
    enum boot_kernel_mode kernel_mode;
};

struct boot_info {
    boot_kernel_mode_info *mode_info;
};

#endif
