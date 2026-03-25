// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_VIDEO_HANDLE_H
#define _ZERO_VIDEO_HANDLE_H

#include <zero/types.h>

struct video_handle;
struct video_handle *video_new ();
usize_t video_width (struct video_handle *handle);
usize_t video_height (struct video_handle *handle);
void video_draw_pixel (struct video_handle *handle, usize_t x, usize_t y,
                       ubyte_t col);

#endif
