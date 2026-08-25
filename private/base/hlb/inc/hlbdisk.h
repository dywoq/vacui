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

//
// Routine Description
//
//      A disk operation status enumeration
//
typedef enum _HLB_DISK_OPERATION_STATUS : UBYTE
{
    HLB_DISK_OPERATION_SUCCESSFUL = 0x00,
    HLB_DISK_OPERATION_INVALID_FUNCTION_OR_PARAMETER = 0x01,
    HLB_DISK_OPERATION_ADDRESS_MARK_NOT_FOUND = 0x02,
    HLB_DISK_OPERATION_WRITE_PROTECTED = 0x03,
    HLB_DISK_OPERATION_SECTOR_NOT_FOUND_OR_READ_ERROR = 0x04,

    //
    // Note
    //
    //      According to the https://www.ctyme.com/intr/rb-0606.htm site,
    //      this status value is platform-dependent. There are two variants:
    //
    //          0x05 -> Reset Failed (Hard disk)
    //          0x05 -> Data did not verify correctly (TI Professional PC)
    //
    HLB_DISK_OPERATION_RESET_FAILED = 0x05,
    HLB_DISK_OPERATION_DATA_NO_CORRECT_VERIFICATION = 0x05,

    HLB_DISK_OPERATION_DISK_CHANGED = 0x06,
    HLB_DISK_OPERATION_DRIVE_PARAMETER_ACTIVITY_FAILED = 0x07,
    HLB_DISK_OPERATION_DMA_OVERRUN = 0x08,
    HLB_DISK_OPERATION_DATA_BOUNDARY_ERROR = 0x09,
    HLB_DISK_OPERATION_BAD_SECTOR_DETECTED = 0x0A,
    HLB_DISK_OPERATION_BAD_TRACK_DETECTED = 0x0B,
    HLB_DISK_OPERATION_UNSUPPORTED_TRACK_OR_INVALID_MEDIA = 0x0C,
    HLB_DISK_OPERATION_INVALID_SECTOR_COUNT_ON_FORMAT = 0x0D,
    HLB_DISK_OPERATION_CONTROL_DATA_ADDRESS_MARK_DETECTED = 0x0E,
    HLB_DISK_OPERATION_DMA_ARBITRATION_LEVEL_OUT_OF_RANGE = 0x0F,
    HLB_DISK_OPERATION_UNCORRECTABLE_CRC_OR_ECC_ERROR = 0x10,
    HLB_DISK_OPERATION_DATA_ECC_CORRECTED = 0x11,
    HLB_DISK_OPERATION_CONTROLLER_FAILURE = 0x20,
    HLB_DISK_OPERATION_NO_MEDIA_IN_DRIVE = 0x31,
    HLB_DISK_OPERATION_INCORRECT_DRIVE_TYPE_IN_CMOS = 0x32,
    HLB_DISK_OPERATION_SEEK_FAILED = 0x40,
    HLB_DISK_OPERATION_TIMEOUT = 0x80,
    HLB_DISK_OPERATION_DRIVE_NOT_READY = 0xAA,
    HLB_DISK_OPERATION_VOLUME_NOT_LOCKED = 0xB0,
    HLB_DISK_OPERATION_VOLUME_LOCKED = 0xB1,
    HLB_DISK_OPERATION_VOLUME_NOT_REMOVABLE = 0xB2,
    HLB_DISK_OPERATION_VOLUME_IN_USE = 0xB3,
    HLB_DISK_OPERATION_LOCK_COUNT_EXCEEDED = 0xB4,
    HLB_DISK_OPERATION_VALID_EJECT_REQUEST_FAILED = 0xB5,
    HLB_DISK_OPERATION_VOLUME_PRESENT_BUT_READ_PROTECTED = 0xB6,
    HLB_DISK_OPERATION_UNDEFINED_ERROR = 0xBB,
    HLB_DISK_OPERATION_WRITE_FAULT = 0xCC,
    HLB_DISK_OPERATION_STATUS_REGISTER_ERROR = 0xE0,
    HLB_DISK_OPERATION_SENSE_OPERATION_FAILED = 0xFF,
} HLB_DISK_OPERATION_STATUS;

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

typedef UBYTE HLB_DISK_EXTENDED_WRITE_FLAG;
#define HLB_DISK_EXTENDED_WRITE_FLAG_VERIFY_WRITE 1 << 0

//
// Routine Description
//
//      Provides the latest disk operation status.
//
//      If the BIOS interrupt handler sets carry flag, the function clears it
//      forcefully. The set carry flag indicates that operation status is not
//      [HLB_DISK_OPERATION_SUCCESSFUL].
//
//
//      See more information: https://www.ctyme.com/intr/rb-0606.htm
//
HLB_DISK_OPERATION_STATUS
HlbGetDiskOperationStatus(HLB_DRIVE_NUMBER DriveNumber);

//
// Routine Description
//
//      Reads data from the drive.
//
//      In this function, the `Dap.Offset` and `Dap.Segment` fields specify
//      destination buffer address. The `Dap.LbaStart` field tells where to
//      read memory. The `Dap.SectorsCount` field shows how much sectors 
//      to read.
//
//      If the carry flag is set, the function forcefully clears it.
// 
//      See more information: https://www.ctyme.com/intr/rb-0708.htm
//
// Returns
//
//      true
//
//          If the carry flag is not set, and the Dap parameter is not null.
//
//      false
//
//          If the carry flag is set or the Dap parameter is null.
//
bool
HlbDiskExtendedRead(
    HLB_DRIVE_NUMBER DriveNumber,
    const HLB_DAP   *Dap
);

//
// Routine Description
//
//      Writes buffer to the drive.
//
//      In this function, the `Dap.Offset` and `Dap.Segment` fields specify
//      source buffer address. The `Dap.LbaStart` field tells where to
//      write memory in the drive. The `Dap.SectorsCount` field shows how 
//      much sectors to write.
//
//      If the carry flag is set, the function forcefully clears it.
// 
//      See more information: https://www.ctyme.com/intr/rb-0710.htm
//
// Returns
//
//      true
//
//          If the carry flag is not set, and the Dap parameter is not null.
//
//      false
//
//          If the carry flag is set or the Dap parameter is null.
//
bool
HlbDiskExtendedWrite(
    HLB_DRIVE_NUMBER             DriveNumber,
    const HLB_DAP               *Dap,
    HLB_DISK_EXTENDED_WRITE_FLAG Flags
);

#endif
