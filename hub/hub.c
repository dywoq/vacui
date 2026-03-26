// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/boot/info.h>
#include <zero/video/video.h>

void hub (struct boot_info *info)
{
        video_draw_pixel (3, 3, 234);
        video_draw_pixel (3, 4, 124);

        if (info->mem_map->entries_count > 1) {
                video_draw_pixel (3, 5, 6);
        }

        int y = 6;
        for (usize_t i = 0; i < info->mem_map->entries_count; i++) {
                auto mem_entry = info->mem_map->entries[i];
                video_draw_pixel(3, y, mem_entry->type);
                y++;
        }

        while (true)
                asm volatile ("hlt\n");
}
