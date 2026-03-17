// Copyright 2026 - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>

static enum bios_vid_mode mode_ = BIOS_VID_TEXT_X80_25;

void bios_vid_tt_output(char ch) {
    __asm__ volatile("movb $0x0e, %%ah\n\t"
                     "movb $0x00, %%bh\n\t"
                     "int $0x10"
                     :
                     : "a"(ch)
                     : "bh");
}

void bios_vid_mode_set(enum bios_vid_mode mode) {
    mode_ = mode;
    __asm volatile("mov %0, %%ax\n"
                   "int $0x10\n"
                   :
                   : "r"(mode)
                   : "ax");
}

uword_t bios_vid_width() {
    if (mode_ == BIOS_VID_TEXT_X80_25) {
        return 80;
    }
    return 0;
}

uword_t bios_vid_height() {
    if (mode_ == BIOS_VID_TEXT_X80_25) {
        return 25;
    }
    return 0;
}

enum bios_vid_mode bios_vid_mode() { return mode_; }
