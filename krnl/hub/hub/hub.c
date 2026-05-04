// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Generic entry function of kernel

void hub()
{
    while (1)
        __asm volatile("wfi\n");
}
