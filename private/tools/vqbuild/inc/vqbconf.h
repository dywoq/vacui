/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        Configuration parsing and management
*/

#ifndef _VQBCONF_H
#define _VQBCONF_H

#include <stdio.h>

/*
    Description:

        Configuration parser.

        It's responsible for parsing the configs and returning
        a map with their keys and values.
*/
typedef struct _VQBCONF_PARSER VQBCONF_PARSER;

/*
    Description:

        Allocates a memory for the VQBCONF_PARSER struct data,
        and returns a pointer to it.

        Returns null if allocating failed.
*/
VQBCONF_PARSER *
VqbConfAllocParser(void);

/*
    Description:

        Frees a pointer to VQBCONF_PARSER struct data.
        setting it to null. This function doesn't free automatically
        pointers, stored by user.

        Returns if it's null.

    Parameters:

        - ParserPtr: The pointer to free.
*/
void
VqbConfDestroyParser(VQBCONF_PARSER *ParserPtr);

static inline void
VqbConf__GuardCleanupParser(VQBCONF_PARSER **Parser)
{
    VqbConfDestroyParser(*Parser);
}
/*
    Description:

        A macro guard which allocates a pointer to VQBCONF_PARSER data,
        and destroys the pointer when the variable goes out of scope.
*/
#define VQBCONF_PARSER_GUARD(variableName)              \
    [[gnu::cleanup(VqbConf__GuardCleanupParser)]]       \
    VQBCONF_PARSER *variableName = VqbConfAllocParser()

/*
    Description:

        Sets a pointer to the file stream within a pointer to
        VQBCONF_PARSER struct data. Returns false if:
        - ParserPtr is null;
        - FileStream is null;
        - The underlying lock flag is on.

    Parameters:

        - ParserPtr: The pointer to VQBCONF_PARSER struct data.
        - FileStream: The pointer to file stream, stored inside the
        config parser data.
*/
bool
VqbConfParserSetFStream(
    VQBCONF_PARSER *ParserPtr,
    FILE *FileStream
);

#endif
