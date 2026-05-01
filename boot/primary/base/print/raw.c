// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// An implementation of raw print function from <base/print.h> header.

__asm(".code16gcc");

#include <bios/video.h>

void base_print_raw(const char *str)
{
    for (const char *p = str; *p != '\0'; ++p) {
        bios_teletype_output(*p, 0);
    }
}
