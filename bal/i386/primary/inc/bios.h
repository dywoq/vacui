// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//      This module contains thin wrappers around BIOS services,
//      such as disk, video etc.
#ifndef _BIOS_H
#define _BIOS_H

#include <vqtypes.h>

//
// Video services
//

#define bios_teletype_putch(ch)                                                \
    __asm volatile("int $0x10\n" : : "a"((0x0e << 8) | ch) : "cc", "memory")

#define bios_set_video_mode(mode)                                              \
    __asm volatile("int $0x10\n" : : "a"((0x0 << 8) | mode) : "cc", "memory")

//
// Disk services
//

// Description:
//
//      A Disk Address Packet. It's used in extended disk functionality,
//      such as read and write.
struct bios_dap {
    ubyte_t size;
    ubyte_t reserved;
    ushort_t sectors_count;
    ushort_t offset;
    ushort_t segment;
    ulong_t lba_start;
};

#define bios_extended_read(dpa, drive_number, carry_flag)                      \
    __asm volatile("int $0x13\n"                                               \
                   : "=@ccc"(carry_flag)                                       \
                   : "S"(dpa), "d"(drive_number), "a"(0x42 << 8)               \
                   : "cc", "memory")

#endif
