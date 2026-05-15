// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vqboot.h>

void
pre(struct boot_info *info)
{
    while (true)
        __asm volatile("hlt\n");
}
