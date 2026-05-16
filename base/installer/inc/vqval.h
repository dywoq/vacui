/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This header contains the Video Abstraction Layer (VAL) functionality
 * for printing text and symbols.
 *
 * The implementation of VAL must satisfy:
 * - the character set - CCSID 437
 * (https://en.wikipedia.org/wiki/Code_page_437), but the allowed range is
 * 0-127;
 *
 * - 16 colors (specified in 'VAL_COLOR' enumeration).
 */

#ifndef _VQVAL_H
#define _VQVAL_H

#include <vqdef.h>

/*
 * The enumeration of 4-byte color values, which are used in
 * drawing functions in VAl.
 */
typedef enum _VAL_COLOR : UBYTE
{
    VAL_BLACK = 0,
    VAL_BLUE,
    VAL_GREEN,
    VAL_CYAN,
    VAL_RED,
    VAL_MAGENTA,
    VAL_BROWN,
    VAL_LIGHT_GRAY,
    VAL_DARK_GRAY,
    VAL_LIGHT_BLUE,
    VAL_LIGHT_GREEN,
    VAL_LIGHT_CYAN,
    VAL_LIGHT_RED,
    VAL_LIGHT_MAGENTA,
    VAL_YELLOW,
    VAL_BRIGHT_WHITE,
} VAL_COLOR;

/*
 * Draws a character at specified position and in specified color.
 * Returns if given position is overflowing the maximum resolution.
 */
void
ValDrawCharacter(
    BYTE character,
    USIZE row,
    USIZE column,
    VAL_COLOR foregroundColor,
    VAL_COLOR backgroundColor
);

/*
 * Draws a string at specified position and in specified color.
 * Its characters share the same row but the column is increased during
 * printing.
 *
 * Returns if given position is overflowing the maximum resolution.
 */
void
ValDrawString(
    const BYTE *string,
    USIZE row,
    USIZE column,
    VAL_COLOR foregroundColor,
    VAL_COLOR backgroundColor
);

/*
 * Provides the maximum rows amount.
 */
USIZE
ValGetRows();

/*
 * Provides the maximum columns amount.
 */
USIZE
ValGetColumns();

/*
 * Clears a screen with given color.
 */
void
ValClear(VAL_COLOR color);

#endif
