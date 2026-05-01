// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// A BIOS-associated header for time management, including the real-time one.

#ifndef _BIOS_TIME_H
#define _BIOS_TIME_H

#include <vacui/types.h>

typedef struct bios_clock_time {
    vac_ubyte_t hour;
    vac_ubyte_t minutes;
    vac_ubyte_t seconds;
    vac_ubyte_t daylight_savings_flag;
} bios_clock_time_t;

typedef struct bios_clock_date {
    vac_ubyte_t century;
    vac_ubyte_t year;
    vac_ubyte_t month;
    vac_ubyte_t day;
} bios_clock_date_t;

bool bios_clock_time_get_rt(bios_clock_time_t *time);
bool bios_clock_date_get_rt(bios_clock_date_t *date);

#endif
