// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

__asm(".code16");

#include <bios/video.h>
#include <zero/types.h>

void entry()
{
    bios_video_mode_set(0x13);
    while (true)
    {
        __asm volatile("hlt\n" : : :);
    }
}
