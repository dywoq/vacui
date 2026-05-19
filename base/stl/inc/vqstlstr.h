/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * This header defines the string function operations.
 */

#ifndef _VQSTLSTR_H
#define _VQSTLSTR_H

#include <vqdef.h>

typedef enum _STLSTR_ERROR : USHORT
{
    STLSTR_OK = 0,
    STLSTR_NULL_STR = 1,
    STLSTR_NULL_DEST_LEN = 2,
} STLSTR_ERROR;

/*
 * Provides the length of given string without including null terminator.
 * The function iterates over the string until it encounters the null
 * terminator, therefore the string must be null-terminated (\0).
 *
 * Errors:
 * - STLSTR_NULL_STR: If str is null
 * - STLSTR_NULL_DEST_LEN: If destLen is null
 */
[[nodiscard]]
STLSTR_ERROR
StlGetStringLen(
    USIZE *destLen,
    const char *str
);

#endif
