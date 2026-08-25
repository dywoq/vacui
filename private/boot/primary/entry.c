//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//       VQBoot primary stage entry
//

__asm(".code16gcc");

#include "print.h"

#include <hlbdisk.h>
#include <vqdef.h>

void
PrimaryEntry(HLB_DRIVE_NUMBER DriveNumber)
{
    bool Okay = HlbDiskExtendedRead(
        DriveNumber, &(HLB_DAP){.Size = 16,
                                .Reserved = 0,
                                .SectorsCount = 2,
                                .Offset = 0x0000,
                                .Segment = 0x1000,
                                .LbaStart = 128}
    );
    if (!Okay)
    {
        PrimaryPrintMsg("Hi!\n\r");
    }

    while (true)
    {
        __asm volatile("hlt\n");
    }
}
