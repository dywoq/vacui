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
    HLB_DISK_OPERATION_STATUS OperationStatus =
        HlbGetDiskOperationStatus(DriveNumber);
    if (OperationStatus == HLB_DISK_OPERATION_INVALID_FUNCTION_OR_PARAMETER)
    {
        PrimaryPrintMsg("The disk operation status is 0x01.\n\r");
    }
}
