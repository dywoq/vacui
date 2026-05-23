// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//      This module contains thin wrappers around BIOS services,
//      such as disk, video etc.
#ifndef _BIOS_H
#define _BIOS_H

#include <vqtypes.h>

// Video service
#define bios_teletype_putch(ch)                                                \
    __asm volatile("int $0x10\n" : : "a"((0x0e << 8) | ch) : "cc", "memory")
#define bios_set_video_mode(mode)                                              \
    __asm volatile("int $0x10\n" : : "a"((0x0 << 8) | mode) : "cc", "memory")

#endif
