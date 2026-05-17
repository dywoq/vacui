/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This header contains the functionality for printing messages
 * into the screen. They wrap around VAL (vqinstval.h).
 *
 * Part of Vacui VQ installer.
 */

#ifndef _VQINSTPRINT_H
#define _VQINSTPRINT_H

#include <vqdef.h>
#include <vqinstval.h>

/*
 * Sets a background color, which applies to all printed characters.
 */
void
PrintSetBgColor(VAL_COLOR color);

/*
 * Sets a foreground color, which is applied to all printed characters.
 */
void
PrintSetFgColor(VAL_COLOR color);

/*
 * Provides the current set background color.
 * The default one is VAL_BLACK.
 */
[[nodiscard]]
VAL_COLOR
PrintGetBgColor();

/*
 * Provides the current set foreground color.
 * The default one is VAL_BRIGHT_WHITE.
 */
[[nodiscard]]
VAL_COLOR
PrintGetFgColor();

/*
 * Clears the whole screen, using the current set background color.
 */
static inline void
PrintClearScreen()
{
    ValClear(PrintGetBgColor());
}

/*
 * Prints a string at fixed position (row, column), using the set foreground
 * and background colors.
 */
void
PrintStrFixed(
    const char *str,
    USIZE row,
    USIZE column
);

#endif
