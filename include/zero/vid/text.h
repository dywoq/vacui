// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/part

#ifndef _ZERO_VID_TEXT_H
#define _ZERO_VID_TEXT_H

#include <zero/types.h>

static constexpr usize_t vid_text_width = 80;
static constexpr usize_t vid_text_height = 25;

void vid_text_putc (char ch, ubyte_t fg_color, ubyte_t bg_color, ubyte_t row,
                    ubyte_t col);
void vid_text_put (const char *str, ubyte_t fg_color, ubyte_t bg_color,
                   ubyte_t row, ubyte_t col);

#endif
