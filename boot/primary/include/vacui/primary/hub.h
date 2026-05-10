// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#ifndef _VACUI_PRIMARY_HUB_H
#define _VACUI_PRIMARY_HUB_H

#include <vacui/primary/bios.h>

#define __hub [[gnu::section (".hub")]]

// storage
__hub extern struct boot_info hub_boot_info;
__hub extern struct bios_dpa hub_kernel_dap;

// print functions
__hub void hub_puts (const char *str);

// panic
[[noreturn]] __hub void hub_panic (const char *msg);

#endif
