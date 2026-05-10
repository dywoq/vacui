// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm (".code16gcc");

#include <vacui/primary/bios.h>

__bios void bios_tt_output (char ch)
{
        __asm volatile ("int $0x10\n"
                        :
                        : "a"((0x0E << 8) | ch)
                        : "cc", "memory");
}

__bios void bios_set_vid_mode (unsigned char mode)
{
        __asm volatile ("int $0x10\n" : : "a"(mode) : "cc", "memory");
}
