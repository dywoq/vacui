// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_BOOT_INFO_H
#define _ZERO_BOOT_INFO_H

#include <zero/types.h>

struct boot_vid_info {
        uword_t vga_mode;
        uword_t width;
        uword_t height;
};

enum boot_mem_entry_type : udword_t {
        BOOT_MEM_ENTRY_RAM = 1,
        BOOT_MEM_ENTRY_RESERVED,
        BOOT_MEM_ENTRY_ACPI,
        BOOT_MEM_ENTRY_NVS,
        BOOT_MEM_ENTRY_UNUSABLE,
        BOOT_MEM_ENTRY_DISABLED = 7,
};

struct boot_mem_entry {
        udword_t base_address_low;
        udword_t base_address_high;
        udword_t length_low;
        udword_t length_high;
        enum boot_mem_entry_type type;
};

struct [[gnu::packed]] boot_mem_map {
        udword_t entries_count;
        struct boot_mem_entry *entries[];
};

enum boot_mode_type {
        BOOT_MODE_TROOT = 0,
        BOOT_MODE_GUI = 1,
};

struct boot_mode_info {
       enum boot_mode_type mode; 
};

struct [[gnu::packed]] boot_info {
        struct boot_vid_info *vid;
        struct boot_mem_map *mem_map;
        struct boot_mode_info *mode;
};

static struct boot_info *boot_info_inst = nullptr;

#endif
