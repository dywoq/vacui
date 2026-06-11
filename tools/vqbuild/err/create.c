/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of construct functions

*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vqberr.h>

VQBERR *
VqbCreateErrMsg(const char *message)
{
    VQBERR *err = malloc(sizeof(VQBERR));
    if (!err)
    {
        return NULL;
    }

    if (!message)
    {
        return err;
    }

    size_t len   = strlen(message) + 1;
    err->message = malloc(len);
    if (!err->message)
    {
        return err;
    }

    strncpy(err->message, message, len);
    return err;
}

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

    char *buf = malloc(size + 1);
    if (!buf)
    {
        return err;
    }

    va_list args_2;
    va_start(args_2, fmt);
    size = vsnprintf(buf, size + 1, fmt, args_2);
    va_end(args_2);
    if (size < 0)
    {
        return err;
    }

    err->message = buf;
    return err;
}
