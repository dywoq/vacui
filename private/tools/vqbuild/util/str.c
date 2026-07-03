/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description;

        An implementation of string utility functions
*/

#include <ctype.h>
#include <string.h>
#include <vqbstrutil.h>

/* Trim functions */

char *
VqbStrTrimLeft(char *String)
{
    if (!String)
    {
        return nullptr;
    }

    while (*String != '\0' && isspace((unsigned char)*String))
    {
        String++;
    }

    return String;
}

char *
VqbStrTrimRight(char *String)
{
    if (!String)
    {
        return nullptr;
    }
    size_t length = strlen(String);
    while (length > 0 && isspace((unsigned char)String[length - 1]))
    {
        length--;
    }
    String[length] = '\0';
    return String;
}

size_t
VqbStrGetIndexOfChar(
    const char *StringPtr,
    char CharToFind
)
{
    if (!StringPtr)
    {
        return -1;
    }

    size_t charIndex = 0;
    for (const char *stringCurrentPtr = StringPtr; *stringCurrentPtr != '\0';
         ++stringCurrentPtr)
    {
        if (CharToFind == *stringCurrentPtr)
        {
            return charIndex;
        }
        charIndex++;
    }

    return -1;
}
