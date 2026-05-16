/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This header contains the functionality for printing messages
 * into the screen. They wrap around VAL (vqinstval.h).
 *
 * Part of Vacui VQ installer.
 */

#include <vqdef.h>
#include <vqinstval.h>

static VAL_COLOR foregroundColor_ = VAL_BLACK;
static VAL_COLOR backgroundColor_ = VAL_BRIGHT_WHITE;

void
PrintSetBgColor(VAL_COLOR color)
{
    backgroundColor_ = color;
}

void
PrintSetFgColor(VAL_COLOR color)
{
    foregroundColor_ = color;
}

[[nodiscard]]
VAL_COLOR
PrintGetBgColor()
{
    return backgroundColor_;
}

[[nodiscard]]
VAL_COLOR
PrintGetFgColor()
{
    return foregroundColor_;
}

void
PrintStrFixed(
    const char *str,
    USIZE row,
    USIZE column
)
{
    USIZE currentColumn = column;
    for (const char *p = str; *p != '\0'; ++p)
    {
        ValDrawCharacter(
            *p, row, currentColumn, foregroundColor_, backgroundColor_
        );
        currentColumn++;
    }
}
