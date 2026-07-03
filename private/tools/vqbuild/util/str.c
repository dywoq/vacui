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
VqbStrTrimLeft(char *string)
{
    if (!string)
    {
        return nullptr;
    }

    while (*string != '\0' && isspace((unsigned char)*string))
    {
        string++;
    }

    return string;
}

char *
VqbStrTrimRight(char *string)
{
    if (string == NULL)
    {
        return nullptr;
    }
    size_t length = strlen(string);
    while (length > 0 && isspace((unsigned char)string[length - 1]))
    {
        length--;
    }
    string[length] = '\0';
    return string;
}
