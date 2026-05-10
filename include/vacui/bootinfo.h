// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_BOOTINFO_H
#define _VACUI_BOOTINFO_H

enum boot_kernel_mode : unsigned char {
        BOOT_KERNEL_NORMAL = 1,
        BOOT_KERNEL_RECOVERY,
};

enum boot_vga_mode : unsigned char {
        // Graphics Modes
        BOOT_VGA_320X200_16_COLORS = 0x0D,
        BOOT_VGA_640X200_16_COLORS = 0x0E,
        BOOT_VGA_640X350_16_COLORS = 0x10,
        BOOT_VGA_640X480_16_COLORS = 0x12,
        BOOT_VGA_320X200_256_COLORS = 0x13,

        // Text Modes
        BOOT_VGA_40X25_TEXT_16_COLORS = 0x01,
        BOOT_VGA_80X25_TEXT_16_COLORS = 0x03,
};

struct boot_video {
        enum boot_vga_mode vga_mode;
        unsigned short width;
        unsigned short height;
        volatile unsigned char *fb_ptr;
};

struct boot_info {
        struct boot_video *video;
        enum boot_kernel_mode kernel_mode;
};

#endif
