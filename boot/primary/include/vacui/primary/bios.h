// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_PRIMARY_BIOS_H
#define _VACUI_PRIMARY_BIOS_H

#define __bios [[gnu::section (".bios")]]

// video
__bios void bios_tt_output (char ch);
__bios void bios_set_vid_mode (unsigned char mode);

// disk
struct [[gnu::packed]] bios_dpa {
        unsigned char size;
        unsigned char reserved;
        unsigned short sections;
        unsigned short offset;
        unsigned short segment;
        unsigned long long start;
};

[[nodiscard]] __bios bool
bios_disk_extread (struct bios_dpa *dpa, unsigned char drive);

__bios void bios_disk_setstatus (unsigned char code);
[[nodiscard]] __bios unsigned char bios_disk_getstatus();

// keyboard
__bios void bios_get_keystroke (char *scan_code, char *ascii_char);

#endif
