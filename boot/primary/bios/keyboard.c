// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm (".code16gcc");

#include <vacui/primary/bios.h>

__bios void bios_get_keystroke (char *scan_code, char *ascii_char)
{
        if (!scan_code || !ascii_char)
                return;
        unsigned int eax = 0;
        __asm volatile ("int $0x16\n"
                        : "=a"(eax)
                        : "a"(0x00 << 8)
                        : "cc", "memory");
        *scan_code = (eax >> 8) & 0xFF;
        *ascii_char = eax & 0xFF;
}
