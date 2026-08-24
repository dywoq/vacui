//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      HLB Disk master header
//

#ifndef HLBDISK_H
#define HLBDISK_H

#include <vqdef.h>

typedef USHORT HLB_DRIVE_NUMBER;

//
// Routine Description
//
//      This is a Disk Address Packet structure. It is used by extended
//      read/write operations.
//
typedef struct _HLB_DAP
{
    UBYTE  Size;
    UBYTE  Reserved;
    USHORT SectorsCount;
    USHORT Offset;
    USHORT Segment;
    ULONG  LbaStart;
} HLB_DAP;

#endif
