/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Error handling API

*/

#ifndef _VQBERR_H
#define _VQBERR_H

/*
Description:

    An error struct with the underlying message.

    If pointer to this struct  must be freed by the function
    which received it and doesn't plan to forward it back.

*/
typedef struct _VQBERR
{
    char *message;
} VQBERR;

/*
Description:

    Returns a new allocated instance of VQBERR struct,
    copying the message to the underlying struct.

    Returns null if it fails to allocate VQBERR or copy message

Parameters:

    - message: A string, must be null terminated.
*/
VQBERR *
VqbCreateErrMsg(const char *message);

/*
Description:

    Returns a new allocated instance of VQBERR struct,
    formatting message with provided format arguments.

    Returns null if it fails to allocate VQBERR, or instance with null message
    to get format message length or format message itself

Parameters:

    - fmt: Format string
    - ...: Format arguments

*/
VQBERR *
VqbFormatErr(
    const char *fmt,
    ...
);

/*
Description:

    Frees VQBERR struct instance in the memory.
    Ignores it if it's already freed.

Parameters:

    - err: An error instance to free
*/
void
VqbDestroyErr(VQBERR *err);

#endif
