/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * An implementation of getting string length.
 */

#include <vqstlstr.h>

[[nodiscard]]
STLSTR_ERROR
StlGetStringLen(
    USIZE *destLen,
    const char *str
)
{
    if (!destLen)
        return STLSTR_NULL_DEST_LEN;
    if (!str)
        return STLSTR_NULL_STR;
    for (const char *p = str; *p != '\0'; ++p)
        *destLen += 1;
    return STLSTR_OK;
}
