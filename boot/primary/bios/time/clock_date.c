// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// An implementation of the real-time clock date symbols from <bios/time.h>
// header.

__asm(".code16gcc");

#include <bios/time.h>
#include <debug/debug.h>
#include <vacui/types.h>

bool bios_clock_date_get_rt(bios_clock_date_t *date)
{
    debug_raw("Getting clock date\n\r");
    if (!date) {
        debug_raw("Parameter date is null\n\r");
        return false;
    }

    vac_uint_t ecx = 0;
    vac_uint_t edx = 0;
    bool       cf;
    __asm volatile(
        "clc\n" // to avoid bugs (https://www.ctyme.com/intr/rb-2277.htm)
        "int $0x1A\n"
        : "=c"(ecx), "=d"(edx), "=@ccc"(cf)
        : "a"((0x04 << 8))
        : "cc", "memory"
    );
    if (cf) {
        debug_raw("Carry flag is set\n\r");
        return false;
    }

    // Take high/low bits of ECX/EDX registers
    date->century = (vac_ubyte_t)(ecx & (0xFF << 8)) >> 8;
    date->year    = (vac_ubyte_t)(ecx & 0xFF);
    date->month   = (vac_ubyte_t)(edx & (0xFF << 8)) >> 8;
    date->day     = (vac_ubyte_t)(edx & 0xFF);

    debug_raw("Successfully retrieved clock date\n\r");
    return true;
}
