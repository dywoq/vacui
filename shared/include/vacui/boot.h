// Copyright (c) 2026 dywoq
//
// This code is released under the MIT License.
// https://opensource.org/licenses/MIT
//
// Repository:
// https://github.com/dywoq/vacui

// Declarations that let bootloader pass information
// to the kernel.

#ifndef _VACUI_BOOT_H
#define _VACUI_BOOT_H

typedef struct vacui_boot_acpi {
    void *address;
} vacui_boot_acpi_t;

typedef struct vacui_boot_info {
    vacui_boot_acpi_t acpi;
} vacui_boot_info_t;

#endif
