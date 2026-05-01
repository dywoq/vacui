// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// An implementation of the real-time clock time symbols from <bios/time.h>
// header.

__asm(".code16gcc");

#include <bios/time.h>
#include <vacui/types.h>

bool bios_clock_time_get_rt(bios_clock_time_t *time)
{
    if (!time)
        return false;

    vac_uint_t ecx = 0;
    vac_uint_t edx = 0;
    bool       cf;
    __asm volatile(
        "clc\n" // to avoid bugs (see https://www.ctyme.com/intr/rb-2273.htm)
        "int $0x1A\n"
        : "=c"(ecx), "=d"(edx), "=@ccc"(cf)
        : "a"((0x02 << 8))
        : "cc", "memory"
    );
    if (cf)
        return false;

    // Take high/low bits of ECX/EDX registers
    time->hour                  = (vac_ubyte_t)(ecx & (0xFF << 8)) >> 8;
    time->minutes               = (vac_ubyte_t)(ecx & 0xFF);
    time->seconds               = (vac_ubyte_t)(edx & (0xFF << 8)) >> 8;
    time->daylight_savings_flag = (vac_ubyte_t)(edx & 0xFF);

    return true;
}
