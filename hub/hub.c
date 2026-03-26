// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/boot/info.h>
#include <zero/video/video.h>

void hub (struct boot_info *info)
{
        video_draw_pixel (3, 3, 234);
        video_draw_pixel (3, 4, 124);
        while (true)
                asm volatile ("hlt\n");
}
