// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_BOOT_INFO_H
#define _ZERO_BOOT_INFO_H

#include <stdint.h>

struct zr_boot_video_info {
        uint16_t mode;
        uint16_t width;
        uint16_t height;
};

struct zr_boot_info {
        struct zr_boot_video_info *video;
};

#endif
