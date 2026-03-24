// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <stdint.h>
#include <zero/boot/info.h>
#include <zero/drvs/vid/reg.h>

// Initializes subsystems.
void ss_init (void)
{
        // Drivers
        drvs_vid_allreg ();
        drvs_vid_init ();
}

void hub (struct boot_info *info)
{
        ss_init ();
        while (true)
                asm volatile ("hlt\n");
}
