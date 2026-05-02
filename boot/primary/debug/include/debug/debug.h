// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Debug print macros, that are expanded if CONFIG_BASE_DEBUG_STATUS is 1.

#ifndef _DEBUG_DEBUG_H
#define _DEBUG_DEBUG_H

#include <base/print.h>
#include <generated/config.h>

#if CONFIG_BASE_DEBUG_STATUS
#define base_debug_raw(str) base_print_raw("| DEBUG: " str)
#else
#define base_debug_raw()
#endif

#endif
