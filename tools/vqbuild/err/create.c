/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of construct functions

*/

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

    size_t messageLength = strlen(message) + 1;
    err->message         = malloc(messageLength);
    if (!err->message)
    {
        return err;
    }

    strncpy(err->message, message, messageLength);
    return err;
}
