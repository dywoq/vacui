// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/boot/info.h>
#include <zero/types.h>
#include <zero/vid/text.h>

#define VRAM_ 0xB8000

void vid_text_putc (char ch, ubyte_t fg_color, ubyte_t bg_color, ubyte_t row,
                    ubyte_t col)
{
        int index = (row * vid_text_width + col) * 2;
        volatile ubyte_t *vram = (ubyte_t *)VRAM_;
        vram[index] = ch;
        vram[index + 1] = (bg_color << 4) | fg_color;
}

void vid_text_put (const char *str, ubyte_t fg_color, ubyte_t bg_color,
                   ubyte_t row, ubyte_t col)
{
        ubyte_t col_idx = col;
        ubyte_t row_idx = row;
        for (const char *p = str; *p != '\0'; ++p) {
                char ch = *p;
                if (ch == '\n') {
                        row_idx++;
                        col_idx = col;
                        continue;
                }
                vid_text_putc (ch, fg_color, bg_color, row_idx, col_idx);
                col_idx++;
        }
}
