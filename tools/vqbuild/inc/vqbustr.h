/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    String utility functions for C99

*/

#ifndef _VQBUSTR_H
#define _VQBUSTR_H

#include <stddef.h>

/*
Description:

    Finds a character in the given string, and returns
    its position in case of success.

    Returns SIZE_MAX if:
    - the function fails to find character
    - string is null

Parameters:

    - character: The character to find.

    - string: The character to find in the string.
    It must be null-terminated.

*/
size_t
VqbUStrFindCharacter(
    char character,
    const char *string
);

#endif
