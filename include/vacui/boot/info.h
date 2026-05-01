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

typedef struct vq_boot_info_time {
    vac_ubyte_t hours;
    vac_ubyte_t minutes;
    vac_ubyte_t seconds;
    vac_ubyte_t century;
    vac_ubyte_t year;
    vac_ubyte_t month;
    vac_ubyte_t day;
    vac_ubyte_t daylight_savings_flag;
} vq_boot_info_time_t;

typedef struct vq_boot_info {
    vq_boot_info_time_t *time;
} vq_boot_info_t;

#endif
