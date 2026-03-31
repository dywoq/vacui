// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_BOOT_INFO_HXX
#define _ZERO_BOOT_INFO_HXX

#include "../types.hxx"

extern "C" struct Zr_BootInfoVideo
{
    zero::UWord vgaMode;
    zero::UWord width;
    zero::UWord height;
};

extern "C" enum Zr_BootInfoMemoryMapEntryType : zero::UDWord
{
    ZR_BOOT_INFO_MEMORY_MAP_USABLE = 1,
    ZR_BOOT_INFO_MEMORY_MAP_RESERVED,
    ZR_BOOT_INFO_MEMORY_MAP_ACPI,
    ZR_BOOT_INFO_MEMORY_MAP_NVS,
    ZR_BOOT_INFO_MEMORY_MAP_UNUSABLE,
    ZR_BOOT_INFO_MEMORY_MAP_DISABLED = 7,
};

extern "C" struct Zr_BootInfoMemoryMapEntry
{
    zero::UDWord baseAddressLow;
    zero::UDWord baseAddressHigh;
    zero::UDWord lengthLow;
    zero::UDWord lengthHigh;
    enum Zr_BootInfoMemoryMapEntryType type;
};

extern "C" struct Zr_BootInfoMemory
{
    zero::UByte entriesCount;
    struct Zr_BootInfoMemoryMapEntry *entries[];
};

extern "C" struct Zr_BootInfo
{
    struct Zr_BootInfoVideo *video;
    struct Zr_BootInfoMemory *memory;
};

#endif
