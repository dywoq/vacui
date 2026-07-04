/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        An implementation of configuration parser
*/

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <vqbconf.h>

struct _VQBCONF_PARSER
{
    FILE *FileStream;
    atomic_bool IsOn;
};

VQBCONF_PARSER *
VqbConfAllocParser(void)
{
    /* Allocate parser */
    VQBCONF_PARSER *parserPtr = malloc(sizeof(VQBCONF_PARSER));
    if (!parserPtr)
    {
        return nullptr;
    }
    /* Initialize its fields */
    atomic_init(&parserPtr->IsOn, false);
    return parserPtr;
}

void
VqbConfDestroyParser(VQBCONF_PARSER *ParserPtr)
{
    if (!ParserPtr)
    {
        return;
    }
    free(ParserPtr);
    ParserPtr = nullptr;
}

bool
VqbConfParserSetFStream(
    VQBCONF_PARSER *ParserPtr,
    FILE *FileStream
)
{
    if (!ParserPtr || !FileStream)
    {
        return false;
    }
    if (atomic_load(&ParserPtr->IsOn))
    {
        return false;
    }
    ParserPtr->FileStream = FileStream;
    return true;
}
