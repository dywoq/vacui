// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Thin wrappers around BIOS video services interrupts.

#ifndef _BIOS_VIDEO_H
#define _BIOS_VIDEO_H

#include <vacui/types.h>

void bios_teletype_output(
    vac_byte_t  ch,
    vac_ubyte_t page_number
);

#endif
