// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#ifndef _VACUI_BOOT_BIOS_VID_H
#define _VACUI_BOOT_BIOS_VID_H

#include <vacui/abi/c.h>
#include <vacui/types.h>

VACUI_ABI_EXTERN_C
void
BiosTeletypePut(char character);

VACUI_ABI_EXTERN_C
void
BiosSwitchVidMode(UWord mode);

#endif

