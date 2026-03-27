// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_TROOT_PRINT_H
#define _ZERO_TROOT_PRINT_H

#include <zero/types.h>

struct vid_text_pos troot_putc (char ch, ubyte_t row, ubyte_t col);
struct vid_text_pos troot_print (const char *str, ubyte_t row, ubyte_t col);

#endif
