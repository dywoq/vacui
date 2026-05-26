// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

#include <bios.h>

__asm(".code16gcc");

void hprint(const char *str)
{
    for (const char *p = str; *p != '\0'; ++p) {
        bios_teletype_putch(*p);
    }
}
