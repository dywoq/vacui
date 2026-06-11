/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Startup code of vqbuild

*/

#include <stdio.h>
#include <vqberr.h>

int
main()
{

    VQBERR *error = VqbFormatErr("Hi! %d", 2);
    if (error)
    {
        printf(
            "Error message: %s\n", error->message ? error->message : "<null>"
        );
        VqbDestroyErr(error);
    }
    else
    {
        printf("No error\n");
    }

    return 0;
}
