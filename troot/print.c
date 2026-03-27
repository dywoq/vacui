// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/troot/cursor.h>
#include <zero/types.h>
#include <zero/vid/text.h>

struct vid_text_pos troot_putc (char ch, ubyte_t row, ubyte_t col)
{
        struct vid_text_pos pos = vid_text_putc (ch, 15, 0, row, col);
        troot_cursor_set (row, col);
        return pos;
}

struct vid_text_pos troot_print (const char *str, ubyte_t row, ubyte_t col)
{
        struct vid_text_pos pos = vid_text_put (str, 15, 0, row, col);
        troot_cursor_set (row, col);
        return pos;
}
