/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * The VAL implementation for VGA mode 0x03.
 */

#include <vqdef.h>
#include <vqinstval.h>

#define COLUMNS_ 80
#define ROWS_ 25
#define DRAW_TO_TEXT_BUF_(                                                     \
    row, column, character, foregroundColor, backgroundColor                   \
)                                                                              \
    (((volatile USHORT *)0xb8000)[column * COLUMNS_ + row] =                   \
         (character) | (foregroundColor << 8) | (backgroundColor << 12))

#define DRAW_TO_TEXT_BUF_BG_(row, column, character, bg_color)                 \
    (((volatile USHORT *)0xb8000)[column * COLUMNS_ + row] =                   \
         (character) | ((bg_color) << 12))

void
ValDrawCharacter(
    BYTE character,
    USIZE row,
    USIZE column,
    VAL_COLOR foregroundColor,
    VAL_COLOR backgroundColor
)
{
    if (row > ValGetRows() || column > ValGetColumns())
        return;
    DRAW_TO_TEXT_BUF_(row, column, character, foregroundColor, backgroundColor);
}

void
ValDrawString(
    const BYTE *string,
    USIZE row,
    USIZE column,
    VAL_COLOR foregroundColor,
    VAL_COLOR backgroundColor
)
{
    if (row > ValGetRows() || column > ValGetColumns())
        return;
    USIZE currentColumn = column;
    for (const BYTE *p = string; *p != '\0'; ++p)
    {
        DRAW_TO_TEXT_BUF_(row, column, *p, foregroundColor, backgroundColor);
        currentColumn++;
    }
}

USIZE
ValGetRows()
{
    return ROWS_;
}

USIZE
ValGetColumns()
{
    return COLUMNS_;
}

void
ValClear(VAL_COLOR color)
{
    for (USIZE i = 0; i < COLUMNS_; i++)
    {
        for (USIZE j = 0; j < ROWS_; j++)
        {
            DRAW_TO_TEXT_BUF_BG_(i, j, ' ', color);
        }
    }
}
