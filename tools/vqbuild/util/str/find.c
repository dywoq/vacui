/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of find functions

*/

#include <stddef.h>
#include <stdint.h>

size_t
VqbUStrFindCharacter(
    char character,
    const char *string
)
{
    if (!string)
    {
        return SIZE_MAX;
    }

    size_t currentPosition = 0;
    size_t position        = SIZE_MAX;

    for (const char *ptr = string; *ptr != '\0'; ++ptr)
    {
        if (*ptr == character)
        {
            position = currentPosition;
            break;
        }
        currentPosition++;
    }

    return position;
}
