// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_VIDEO_VIDEO_H
#define _ZERO_VIDEO_VIDEO_H

#include <zero/types.h>

extern usize_t video_width;
extern usize_t video_height;
void video_draw_pixel (usize_t x, usize_t y, ubyte_t col);

#endif
