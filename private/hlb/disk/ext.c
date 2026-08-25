//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      Extended functions implementation
//

__asm(".code16gcc");

#include <hlbdisk.h>

bool
HlbDiskExtendedRead(
    HLB_DRIVE_NUMBER DriveNumber,
    const HLB_DAP   *Dap
)
{
    if (!Dap)
    {
        return false;
    }
    bool Carry;
    __asm volatile("int $0x13"
                   : "=@ccc"(Carry)
                   : "a"(0x42 << 8), "d"(DriveNumber), "S"(Dap));
    if (Carry)
    {
        __asm volatile("clc\n");
    }
    return !Carry;
}

bool
HlbDiskExtendedWrite(
    HLB_DRIVE_NUMBER             DriveNumber,
    const HLB_DAP               *Dap,
    HLB_DISK_EXTENDED_WRITE_FLAG Flags
)
{
    if (!Dap)
    {
        return false;
    }
    bool Carry;
    __asm volatile("int $0x13"
                   : "=@ccc"(Carry)
                   : "a"((0x43 << 8) | Flags), "d"(DriveNumber), "S"(Dap));
    if (Carry)
    {
        __asm volatile("clc\n");
    }
    return !Carry;
}
