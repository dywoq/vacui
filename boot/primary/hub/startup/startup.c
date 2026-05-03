// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Startup function of vqboot_primary.

#include <vacui/types.h>

void startup()
{
    while (true)
        __asm volatile("hlt\n");
}
