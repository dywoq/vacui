// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>

void hub_printnf(const char *str) {
    for (const char *p = str; *p != '\0'; ++p) {
        if (*p == '\n') {
            bios_vid_tt_output('\r');
            bios_vid_tt_output('\n');
            continue;
        }
        bios_vid_tt_output(*p);
    }
}

void hub_printnf_dbg(const char *str) {
#if DEBUG
    hub_printnf("DEBUG: ");
    hub_printnf(str);
#endif
}
