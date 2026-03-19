// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _BIOS_VID_H
#define _BIOS_VID_H

#include <std/types.h>

enum bios_vid_mode : word_t {
    BIOS_VID_TEXT_X80_25 = 0x03,
};

void bios_vid_tt_output(char ch);
void bios_vid_mode_set(enum bios_vid_mode mode);
[[nodiscard]] uword_t bios_vid_width();
[[nodiscard]] uword_t bios_vid_height();
[[nodiscard]] enum bios_vid_mode bios_vid_mode();

#endif
