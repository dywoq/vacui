// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/boot/info.h>
#include <zero/troot/entry.h>

void hub (struct boot_info *info)
{
        boot_info_inst = info;

        if (info->mode->mode == BOOT_MODE_TROOT)
                troot_entry ();

        while (true)
                asm volatile ("hlt\n");
}
