//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      This header defines type, macro and structs of VQ Filesystem
//      (or VQFS).
//
//      It is meant to be used by host operating system development tools
//      and operating system components, therefore, the header defines its own
//      integer types.
//

#ifndef VQFS_H
#define VQFS_H

//
// Integral types
//

typedef signed char        vqfs_byte_t;
typedef signed short       vqfs_short_t;
typedef signed int         vqfs_int_t;
typedef signed long long   vqfs_long_t;
typedef unsigned char      vqfs_ubyte_t;
typedef unsigned short     vqfs_ushort_t;
typedef unsigned int       vqfs_uint_t;
typedef unsigned long long vqfs_ulong_t;

//
// Constants
//

#define VQFS_BLOCK_SIZE         4096
#define VQFS_BLOCKS_TOTAL_COUNT 524288
#define VQFS_MAJOR_VERSION      1
#define VQFS_MINOR_VERSION      0

//
// Routine Description
//
//      Header information of VQFS, which is at the very start of
//      a formatted drive.
//
//      It contains boot sector code, meta information and offsets to other
//      information data.
//
typedef struct vqfs_header {
    vqfs_ubyte_t boot_sector[512];

    //
    // Version
    //
    vqfs_ushort_t major_version;
    vqfs_ushort_t minor_version;

    //
    // Offsets
    //
    vqfs_uint_t blocks_table_offset;
    vqfs_uint_t root_dir_offset;
    vqfs_uint_t blocks_array_offset;

    //
    // Blocks table information
    //
    vqfs_uint_t blocks_table_max_limit;
    vqfs_uint_t blocks_table_current_count;

    //
    // Root and regular directory information
    //
    vqfs_uint_t regular_dir_max_limit;
    vqfs_uint_t root_dir_current_count;

    //
    // Blocks array information
    //
    vqfs_uint_t blocks_array_max_limit;

    //
    // Padding
    //
    char padding[3548];
} vqfs_header_t;

//
// Routine Description
//
//      Table consisting of block offsets. It is placed after header
//      information.
//
typedef struct vqfs_blocks_table {
    vqfs_uint_t block_offsets[VQFS_BLOCKS_TOTAL_COUNT];
} vqfs_blocks_table_t;

typedef vqfs_uint_t vqfs_time_t;
#define VQFS_TIME_MAKE(hour, minute, second)                                   \
    (vqfs_time_t)(hour | (minute << 8) | (second << 16))
#define VQFS_TIME_GET_HOUR(time)   (vqfs_uint_t)(time & 0xFF)
#define VQFS_TIME_GET_MINUTE(time) (vqfs_uint_t)((time & (0xFF << 8)) >> 8)
#define VQFS_TIME_GET_SECOND(time) (vqfs_uint_t)((time & (0xFF << 16)) >> 16)

//
// Routine Description
//
//      Directory entry flags
//

#define VQFS_DIR_ENTRY_FILE      1 << 0
#define VQFS_DIR_ENTRY_DIRECTORY 1 << 1
#define VQFS_DIR_ENTRY_READONLY  1 << 2
#define VQFS_DIR_ENTRY_HIDDEN    1 << 3
#define VQFS_DIR_ENTRY_SYSTEM    1 << 4

//
// Routine Description
//
//      Directory entry with a name, extension and flags, and meta
//      information, such as creation and last update time. If this is
//      a directory, then its block points to an array of directory entries.
//
typedef struct vqfs_dir_entry {
    char        name[12];
    char        extension[4];
    vqfs_uint_t flags;
    vqfs_time_t time_creation;
    vqfs_time_t time_last_update;
    vqfs_uint_t starting_block_id;
} vqfs_dir_entry_t;

#define VQFS_DIR_ENTRIES_LIMIT VQFS_BLOCK_SIZE / sizeof(struct vqfs_dir_entry)

//
// Routine Description
//
//      Root directory. It is placed after the blocks table.
//
typedef struct vqfs_root_dir {
    vqfs_dir_entry_t dir_entries[VQFS_DIR_ENTRIES_LIMIT];
} vqfs_root_dir_t;

#define VQFS_BLOCK_INDEX_EOF 0xFFFFFFFF

//
// Routine Description
//
//      Block information struct. The next block index is pointing at a
//      block offset in the blocks table.
//
typedef struct vqfs_block {
    vqfs_ubyte_t content[4092];
    vqfs_uint_t  next_block_index;
} vqfs_block_t;

#endif
