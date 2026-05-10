// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_PRIMARY_BIOS_H
#define _VACUI_PRIMARY_BIOS_H

#define __bios [[gnu::section (".bios")]]

// video
struct [[gnu::packed]] bios_vbe_info {
        char signature[4];
        unsigned short version;
        unsigned int oem_string_ptr;
        unsigned int capabilities;
        unsigned int video_modes_ptr;
        unsigned short total_memory;
        unsigned short oem_software_rev;
        unsigned int vendor_name_ptr;
        unsigned int product_name_ptr;
        unsigned int product_rev_ptr;
        unsigned short vbe_af_version;
        unsigned int accel_modes_ptr;
        unsigned char reserved[216];
        unsigned char oem_scratchpad[256];
};

__bios void bios_tt_output (char ch);
__bios void bios_set_vid_mode (unsigned char mode);

[[nodiscard]] __bios bool
bios_get_vbe (struct bios_vbe_info *vbe, unsigned char *status);

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
