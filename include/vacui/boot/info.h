// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// A header with bootloader information declarations.
// They are passed to the kernel from bootloader primary stage.

#ifndef _VACUI_BOOT_INFO_H
#define _VACUI_BOOT_INFO_H

#include <vacui/types.h>

typedef enum vq_boot_mem_entry_enum : vac_uint_t {
    VQ_BOOT_MEM_ENTRY_AVAILABLE = 0x01,
    VQ_BOOT_MEM_ENTRY_RESERVED  = 0x02,
    VQ_BOOT_MEM_ENTRY_ACPI      = 0x03,
    VQ_BOOT_MEM_ENTRY_ACPI_NVS  = 0x04,
} vq_boot_mem_entry_enum_t;

typedef struct vq_boot_mem_entry {
    vac_uint_t               address_low;
    vac_uint_t               address_high;
    vac_uint_t               length_low;
    vac_uint_t               length_high;
    vq_boot_mem_entry_enum_t type;
} vq_boot_mem_entry_t;

typedef struct vq_boot_info {
    vq_boot_mem_entry_t *entries[];
} vq_boot_info_t;

#endif
