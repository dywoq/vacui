// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <stdint.h>
#include <zero/boot/info.h>
#include <zero/video/handle.h>

void hub (struct boot_info *info)
{
        struct video_handle *handle = video_new ();
        video_draw_pixel (handle, 3, 3, 234);
        video_draw_pixel(handle, 3, 4, 124);
        while (true)
                asm volatile ("hlt\n");
}
