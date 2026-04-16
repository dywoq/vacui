// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#include <vacui/boot/bios/vid.h>

__asm(".code16gcc");

void
Hub()
{
    BiosSwitchVidMode(0x13);
    while (true)
        __asm volatile("hlt");
}

