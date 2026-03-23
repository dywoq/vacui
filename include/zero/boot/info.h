// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_BOOT_INFO_H
#define _ZERO_BOOT_INFO_H

#include <zero/types.h>

struct boot_vid_info {
        word_t vga_mode;
        word_t width;
        word_t height;
};

struct boot_info {
        struct boot_vid_info *vid;
};

#endif
