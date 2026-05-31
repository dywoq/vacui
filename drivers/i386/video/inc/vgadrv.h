/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Header-only portable video driver for VGA modes.
    It's usable only if the current AAL is i386.
*/

#ifndef _VGADRV_H
#define _VGADRV_H

#include <vqtypes.h>

typedef ubyte_t vga_text_attribute_t;

/*
Description:

    Type definition for VGA text color
*/
typedef ubyte_t vga_text_color;
#define VGA_TEXT_BLACK      (vga_text_color)0
#define VGA_TEXT_BLUE       (vga_text_color)1
#define VGA_TEXT_GREEN      (vga_text_color)2
#define VGA_TEXT_CYAN       (vga_text_color)3
#define VGA_TEXT_RED        (vga_text_color)4
#define VGA_TEXT_MAGENTA    (vga_text_color)5
#define VGA_TEXT_BROWN      (vga_text_color)6
#define VGA_TEXT_LIGHT_GRAY (vga_text_color)7

/*
Description:

    Forms a 8-bit VGA text mode attribute value, using the given parameters.
    The bit structure:

        | Foreground Color | FG intensity | Background color | BG intensity |
        | 0      1     2   |      3       | 4     5     6    |      7       |
*/
#define VGA_TEXT_FORM_ATTRIBUTE(                                               \
    fg_color, fg_intensity, bg_color, bg_intensity                             \
)                                                                              \
    (vga_text_attribute_t)(                                                    \
        fg_color | (fg_intensity << 3) | (bg_color << 4) | (bg_intensity << 7) \
    )
#define VGA_TEXT_GET_FG_COLOR(attribute)     (attribute & 0x7)
#define VGA_TEXT_GET_FG_INTENSITY(attribute) ((attribute & 0x8) >> 3)
#define VGA_TEXT_GET_BG_COLOR(attribute)     ((attribute & 0x70) >> 4)
#define VGA_TEXT_GET_BG_INTENSITY(attribute) ((attribute & 0x80) >> 7)

/*
Description:

    Standard interface for VGA text video driver.
    It must be implemented (who uses the video driver) and provided to the
    manipulation functions
*/
struct vga_text_iface
{
    /*
    Description:

        Resolution Limit
    */
    ubyte_t columns;
    ubyte_t rows;

    /*
    Description:

        An address to VGA buffer. It can be virtual address, memory-mapped IO
        address, or pointer to the buffer
    */
    volatile ubyte_t *address;
};
struct vga_text_iface vga_text_iface_80x25 = {
    .address = (volatile ubyte_t *)0xb8000,
    .columns = 80,
    .rows    = 25,
};
struct vga_text_iface vga_text_iface_40x25 = {
    .address = (volatile ubyte_t *)0xb8000,
    .columns = 40,
    .rows    = 25,
};

/*
Description:

    Type definition for VGA text mode video driver errors
*/
typedef ubyte_t vga_text_err_t;
#define VGA_TEXT_ERR_OK           (vga_text_err_t)0
#define VGA_TEXT_ERR_OVERFLOW     (vga_text_err_t)1
#define VGA_TEXT_ERR_IFACE_NULL   (vga_text_err_t)2
#define VGA_TEXT_ERR_NULL_ADDRESS (vga_text_err_t)3
#define VGA_TEXT_ERR_BUF_NULL     (vga_text_err_t)4

typedef uint_t vga_text_buf_entry_t;

/*
Description:

    Forms a buffer entry with information packed into one 32-bit value.
    The bit structure:

    |     Character   |       Attribute       |
    | 0 1 2 3 4 5 6 7 | 8 9 10 11 12 13 14 15 |

    |           Row           |        Column           |
    | 16 17 18 19 20 21 22 23 | 24 25 26 27 28 29 30 31 |
*/
#define VGA_TEXT_FORM_BUF_ENTRY(character, row, column, attribute)             \
    (vga_text_buf_entry_t)(                                                    \
        character | (attribute << 8) | (row << 16) | (column << 24)            \
    )
#define VGA_TEXT_GET_CHARACTER(buf_entry) (buf_entry & 0xFF)
#define VGA_TEXT_GET_ATTRIBUTE(buf_entry) ((buf_entry & (0xFF << 8)) >> 8)
#define VGA_TEXT_GET_ROW(buf_entry)       ((buf_entry & (0xFF << 16)) >> 16)
#define VGA_TEXT_GET_COLUMN(buf_entry)    ((buf_entry & (0xFF << 24)) >> 24)

/*
Description:

    Writes a character to iface->address using the following algorithm:

        offset = 2 * (row * iface->columns + column)
        iface->address[offset] = character;
        iface->address[offset + 1] = attribute

Return:

    See 'vga_text_err_t' for errors.

*/
vga_text_err_t vga_text_write(
    struct vga_text_iface *iface,
    const char             character,
    const ubyte_t          row,
    const ubyte_t          column,
    const ubyte_t          attribute
)
{
    if (!iface)
        return VGA_TEXT_ERR_IFACE_NULL;

    if (row > iface->rows || column > iface->columns)
        return VGA_TEXT_ERR_OVERFLOW;

    if (!iface->address)
        return VGA_TEXT_ERR_NULL_ADDRESS;

    ushort_t offset            = 2 * (row * iface->columns + column);
    iface->address[offset]     = character;
    iface->address[offset + 1] = attribute;

    return VGA_TEXT_ERR_OK;
}

/*
Description:

    Writes a entire buffer to iface->address.

    The buffer must contain valid buffer entries, made using
    VGA_TEXT_FORM_BUF_ENTRY macro.

    The write algorithm:

        for buf_entry in buf
            offset = 2 * (buf_entry.row * iface->columns + buf_entry.column);
            iface->address[offset] = buf_entry.character
            iface->address[offset + 1] = buf_entry.attribute

Return:

    See 'vga_text_err_t' for errors.

*/
vga_text_err_t vga_text_write_buf(
    struct vga_text_iface *iface,
    uint_t                *buf,
    const ubyte_t          buf_len
)
{
    if (!iface)
        return VGA_TEXT_ERR_IFACE_NULL;

    if (!iface->address)
        return VGA_TEXT_ERR_NULL_ADDRESS;

    if (!buf)
        return VGA_TEXT_ERR_BUF_NULL;

    uint_t i = 0;
    for (i = 0; i < buf_len; i++)
    {
        if (buf[i] == 0)
            continue;

        ubyte_t row    = VGA_TEXT_GET_ROW(buf[i]);
        ubyte_t column = VGA_TEXT_GET_COLUMN(buf[i]);

        if (row > iface->rows || column > iface->columns)
            return VGA_TEXT_ERR_OVERFLOW;

        vga_text_attribute_t attribute = VGA_TEXT_GET_ATTRIBUTE(buf[i]);

        char character = VGA_TEXT_GET_CHARACTER(buf[i]);

        ubyte_t offset             = 2 * (row * iface->columns + column);
        iface->address[offset]     = character;
        iface->address[offset + 1] = attribute;
    }

    return VGA_TEXT_ERR_OK;
}

#endif
