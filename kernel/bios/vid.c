// Copyright 2026 - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>

void bios_vid_tt_output(char ch) {
    __asm__ volatile("movb $0x0e, %%ah\n\t"
                     "movb $0x00, %%bh\n\t"
                     "int $0x10"
                     :
                     : "a"(ch)
                     : "bh");
}

void bios_vid_mode_set(enum bios_vid_mode mode) {
    __asm volatile("mov %0, %%ax\n"
                   "int $0x10\n"
                   :
                   : "r"(mode)
                   : "ax");
}
