// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      This module defines the standard interface of BAL (Boot Abstraction
//      Layer) information. BAL must pass the information to AAL through the
//      defined structs.
//

#ifndef _VACUIP_BAL_INFO_H
#define _VACUIP_BAL_INFO_H

#include "../types.h"

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
    ushort_t mm_count;
    struct bal_info_mm_entry *entries[];
};

struct bal_info {
    struct bal_info_metadata *metadata;
    struct bal_info_mm_info *mm_info;
};

#endif
