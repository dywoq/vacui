/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of format functions

*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vqberr.h>

VQBERR *
VqbFormatErr(
    const char *fmt,
    ...
)
{
    VQBERR *err = malloc(sizeof(VQBERR));
    if (!err)
    {
        return NULL;
    }

    if (!fmt)
    {
        return NULL;
    }

    va_list args;
    va_start(args, fmt);
    int size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    if (size < 0)
    {
        return err;
    }

    char *buffer = malloc(size + 1);
    if (!buffer)
    {
        return err;
    }

    va_list args2;
    va_start(args2, fmt);
    size = vsnprintf(buffer, size + 1, fmt, args2);
    va_end(args2);
    if (size < 0)
    {
        return err;
    }

    err->message = buffer;
    return err;
}
