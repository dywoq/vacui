// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>

// Will be replaced when we're going to have normal print function
static void print_(const char *msg) {
    for (const char *p = msg; *p != '\0'; ++p) {
        if (*p == '\n') {
            bios_vid_tt_output('\r');
            bios_vid_tt_output('\n');
            continue;
        }
        bios_vid_tt_output(*p);
    }
}

void hub_panic(const char *msg) {
    bios_vid_mode_set(BIOS_VID_TEXT_X80_25);
    print_("--------------- Zero panic ----------------\n");
    print_(msg);
    print_("\n-------------------------------------------");
    while (true) {
        __asm volatile("hlt\n");
    }
}
