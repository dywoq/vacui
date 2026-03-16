// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero


#include <bios/vid.h>
#include <std/types.h>

void hub() {
    bios_vid_mode_set(BIOS_VID_TEXT_X80_25);
    bios_vid_tt_output('A');
    while (true) {
        __asm volatile("hlt\n");
    }
}
