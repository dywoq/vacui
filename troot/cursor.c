// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/drvs/port.h>
#include <zero/types.h>
#include <zero/vid/text.h>

void troot_cursor_set (ubyte_t row, ubyte_t col)
{
        uword_t pos = (uword_t)(row * vid_text_width + col + 1);
        drvs_port_outb (0x0F, 0x3D4);
        drvs_port_outb ((ubyte_t)(pos & 0xFF), 0x3D5);
        drvs_port_outb (0x0E, 0x3D4);
        drvs_port_outb ((ubyte_t)((pos >> 8) & 0xFF), 0x3D5);
}
