// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/types.h>

struct video_handle {
        usize_t width;
        usize_t height;
        volatile ubyte_t *vram;
};

struct video_handle *video_new ()
{
        struct video_handle *handle = nullptr;
        handle->width = 320;
        handle->height = 200;
        handle->vram = (ubyte_t *)0xA0000;
        return handle;
}

usize_t video_width (struct video_handle *handle)
{
        return handle->width;
}

usize_t video_height (struct video_handle *handle)
{
        return handle->height;
}

void video_draw_pixel (struct video_handle *handle, usize_t x, usize_t y,
                       ubyte_t col)
{
        if (x >= handle->width || y >= handle->height)
                return;
        handle->vram[y * handle->width + x] = col;
}
