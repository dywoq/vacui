/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description;

        The vqbuild string utility functions
*/

#ifndef _VQBSTRUTIL_H
#define _VQBSTRUTIL_H

/*
    Description:

        Returns a pointer to the first non-whitespace character
        within an original string. Returns null value if the given pointer to
        the original string is null.

    Parameters:

        - string: A pointer to the original null-terminated string.
*/
char *
VqbStrTrimLeft(char *string);

/*
    Description:

        Removes trailing whitespaces from the end of string.
        It measures the length of the string and scans backwards, decrementing
        underlying length for every whitespace character it finds.

        Once it hits a non-whitespace character, it places a null-terminator
        at that position, cutting off the trailing spaces and returns 
        an original string mutated pointer.

        Returns null value if the given pointer to the original string is null.

    Parameters:

        - string: A pointer to the original null-terminated string.
*/
char *
VqbStrTrimRight(char *string);

#endif
