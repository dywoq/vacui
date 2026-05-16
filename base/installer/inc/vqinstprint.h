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

void
PrintSetBgColor(VAL_COLOR color);

void
PrintSetFgColor(VAL_COLOR color);

[[nodiscard]]
VAL_COLOR
PrintGetBgColor();

[[nodiscard]]
VAL_COLOR
PrintGetFgColor();

static inline void
PrintClearScreen()
{
    ValClear(PrintGetBgColor());
}

void
PrintStrFixed(
    const char *str,
    USIZE row,
    USIZE column
);

#endif
