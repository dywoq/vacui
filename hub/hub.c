// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <stdint.h>
#include <zero/boot/info.h>




void hub (struct boot_info *info)
{

        while (true)
                asm volatile ("hlt\n");
}
