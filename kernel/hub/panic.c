// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>
#include <hub/print.h>

void hub_panic(const char *msg) {
    bios_vid_mode_set(BIOS_VID_TEXT_X80_25);
    hub_printnf("--------------- Zero panic ----------------\n");
    hub_printnf(msg);
    hub_printnf("\n-------------------------------------------");
    while (true) {
        __asm volatile("hlt\n");
    }
}
