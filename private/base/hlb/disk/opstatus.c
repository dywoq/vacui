//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      An implementation of disk operation status management
//

__asm(".code16gcc");

#include <hlbdisk.h>
#include <vqdef.h>

HLB_DISK_OPERATION_STATUS
HlbGetDiskOperationStatus(HLB_DRIVE_NUMBER DriveNumber)
{
    USHORT ActualOperationStatus;
    bool   Carry;

    __asm volatile("int $13\n"
                   : "=a"(ActualOperationStatus), "=@ccc"(Carry)
                   : "a"(0x1 << 8), "d"(DriveNumber));

    if (Carry)
    {
        __asm volatile("clc\n");
    }

    return (ActualOperationStatus >> 8) & 0xFF;
}
