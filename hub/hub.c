// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <stdint.h>
#include <zero/boot/info.h>

void hub (struct boot_info *info)
{
        auto video_info = info->video;
        if (video_info->mode == 0x13) {
                volatile auto vram = (uint16_t *)0xA0000;
                vram[2 * video_info->width + 2] = 5;
                vram[2 * video_info->width + 3] = 5;
        }

        while (true)
                asm volatile ("hlt\n");
}
