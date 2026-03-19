// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _HUB_PRINT_H
#define _HUB_PRINT_H

void hub_printnf(const char *str);

#if DEBUG
#define hub_printnf_dbg(str) hub_printnf("DEBUG: " str)
#else
#define hub_printnf_dbg(str) ((void)0)
#endif

#endif
