// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <bios.h>
#include <hub.h>

HUBAPI void hprint(const char *str)
{
    for (const char *p = str; *p != '\0'; ++p) {
        bios_teletype_putch(*p);
    }
}
