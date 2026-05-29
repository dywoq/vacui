// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      Contains the definitions and functionality that relate to
//      VQFS (VQ Filesystem).

#ifndef _VQFS_H
#define _VQFS_H

#include <vqtypes.h>

// Description:
//
//      Checks if the given signature equals to 'VQFS'.
#define VQFS_HEADER_IS_CORRECT_SIGNATURE(signature)                            \
    (signature[0] == 'V' && signature[1] == 'Q' && signature[2] == 'F' &&      \
     signature[3] == 'S')

// Description:
//
//      A VQ filesystem header information, containing necessary information for
//      manipulating entries and their data. The structure fully equals to 4KiB.
struct [[gnu::packed]] vqfs_header {
    char signature[4];
    uint_t entry_offsets_offset;
    char pad[4088];
};

#define VQFS_ENTRY_OFFSETS_MAX_SIZE 1024

// Description:
//
//      Table of VQ filesystem entries offsets. The structure fully
//      equals to 4KiB.
struct vqfs_entry_offsets {
    ulong_t entries_offsets[VQFS_ENTRY_OFFSETS_MAX_SIZE];
};

// Entry flags
#define VQFS_ENTRY_FLAG_READABLE 1 << 0
#define VQFS_ENTRY_FLAG_WRITABLE 1 << 1
#define VQFS_ENTRY_FLAG_SYSTEM 1 << 2
#define VQFS_ENTRY_FLAG_HIDDEN 1 << 3
#define VQFS_ENTRY_FLAG_DIR 1 << 4
#define VQFS_ENTRY_FLAG_FILE 1 << 5

// Description:
//
//      Checks if num has flag (VQFS_ENTRY_FLAG_*).
#define VQFS_ENTRY_HAS_FLAG(num, flag) ((num & flag) != 0)

// Description:
//
//      VQ filesystem entry structure.
//
// Notes:
//
//      - If entry is a directory, then blocks_offsets will contain indexes
//      of its files and sub-directories inside array of entries offsets
//      in vqfs_entry_offsets.
struct [[gnu::packed]] vqfs_entry {
    char filename[8];
    char extension[3];
    ubyte_t flags;
    uint_t blocks_offsets[128];
    uint_t file_size;
    char pad[496];
};

#endif
