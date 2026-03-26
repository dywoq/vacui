// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/types.h>

static volatile ubyte_t *vram_ = (ubyte_t *)0xA0000;

usize_t video_width = 320;
usize_t video_height = 200;

void video_draw_pixel (usize_t x, usize_t y, ubyte_t col)
{
        vram_[y * video_width + x] = col;
}
