//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//       VQBoot primary stage entry
//

__asm(".code16gcc");

#include <hlbdisk.h>
#include <vqdef.h>

void
PrimaryEntry(HLB_DRIVE_NUMBER DriveNumber)
{
    while (true)
    {
        __asm volatile("hlt\n");
    }
}
