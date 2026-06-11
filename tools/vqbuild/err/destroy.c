/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of destroy function

*/

#include <stdlib.h>
#include <vqberr.h>

void
VqbDestroyErr(VQBERR *err)
{
    if (!err)
    {
        return;
    }

    if (err->message)
    {
        free(err->message);
    }

    free(err);
}
