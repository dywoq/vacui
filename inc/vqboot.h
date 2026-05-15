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
            dd boot_kernel_mode
            ; ...
 * - The kernel is 32-bit.
 * - The memory layout must match.
 */
static_assert(sizeof(void *) == 4, "size of pointer must be 4 bytes");

enum boot_kernel_mode : ubyte_t {
    BOOT_KERNEL_NORMAL = 0,
    BOOT_KERNEL_RECOVERY,
};

enum boot_vga_mode : ubyte_t {
    BOOT_VGA_320_200_256_COLORS = 0x13,
};

enum boot_mm_entry_type : uint_t {
    BOOT_MM_ENTRY_RAM = 1,
    BOOT_MM_ENTRY_RESERVED,
    BOOT_MM_ENTRY_ACPI,
    BOOT_MM_ENTRY_NVS,
    BOOT_MM_ENTRY_UNUSABLE,
    BOOT_MM_ENTRY_DISABLED = 7
};

struct boot_mm_entry {
    uint_t base_address_low;
    uint_t base_address_high;
    uint_t length_low;
    uint_t length_high;
    enum boot_mm_entry_type type;
};

struct [[gnu::packed]] boot_mm_info {
    uint_t entries_count;
    struct boot_mm_entry *entires[];
};

struct boot_kernel_mode_info {
    enum boot_kernel_mode kernel_mode;
};

struct boot_video_info {
    enum boot_vga_mode vga_mode;
    uint_t width;
    uint_t height;
    ushort_t colors_count;
    volatile ubyte_t *ptr;
};

struct boot_info {
    struct boot_kernel_mode_info *mode_info;
    struct boot_video_info *video_info;
    struct boot_mm_info *mm;
};

#endif
