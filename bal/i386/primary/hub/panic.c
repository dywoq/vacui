// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <bios.h>
#include <hub.h>

HUBAPI void hpanic(const char *msg)
{
    bios_set_video_mode(0x03);
    hprint("[Vacui i386 BAL] Panicking:\n\r");
    hprint(msg);
    while (true)
        __asm volatile("hlt\n");
}
