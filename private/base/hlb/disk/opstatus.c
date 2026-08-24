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
HlbGetDiskOperationStatus()
{
    USHORT ActualOperationStatus;
    __asm volatile("int $13\n" : "=a"(ActualOperationStatus));
    return (ActualOperationStatus >> 8) & 0xFF;
}
