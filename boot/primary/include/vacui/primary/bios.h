// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_PRIMARY_BIOS_H
#define _VACUI_PRIMARY_BIOS_H

#define __bios [[gnu::section(".bios")]]

__bios void bios_tt_output(char ch);

#endif
