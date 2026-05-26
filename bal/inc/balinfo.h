// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      This module defines the standard interface of BAL (Boot Abstraction
//      Layer) information. BAL must pass the information to AAL through the
//      defined structs.
//
//      The BAL information is NEVER accessed directly by generic kernel code.
//      AAL's PAL processes BAL and gives
//

#ifndef _BALINFO_H
#define _BALINFO_H

#include <vqtypes.h>

struct bal_info_metadata {
    const char *name;
    const char *license;
};

enum bal_info_mm_entry_type : ushort_t {
    BAL_INFO_MM_ENTRY_FREE = 0,
    BAL_INFO_MM_ENTRY_RESERVED = 1,
};

struct bal_info_mm_entry {
    ulong_t address;
    ulong_t length;
    enum bal_info_mm_entry_type type;
};

struct bal_info_mm_info {
    ushort_t entries_count;
    // If it's false, this means BAL completely skipped the process of fetching
    // memory map. For example: Unlike x86, RISC-V, and other plates do not have
    // unified memory map. PAL manages it, creates its own custom memory map and
    // provides it to the generic kernel.
    bool entries_present;
    struct bal_info_mm_entry *entries[];
};

enum bal_info_kernel_mode : ubyte_t {
    BAL_INFO_KERNEL_NORMAL = 0,
    BAL_INFO_KERNEL_RECOVERY,
};

struct bal_info {
    struct bal_info_metadata *metadata;
    struct bal_info_mm_info *mm_info;
    enum bal_info_kernel_mode kernel_mode;
};

#endif
