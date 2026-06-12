/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of construct functions from vqblex.h

*/

#include <stdlib.h>
#include <vqblex.h>

VQBLEX *
VqbCreateLexer(FILE *fileStream)
{
    VQBLEX *lexer = malloc(sizeof(VQBLEX));
    if (!lexer)
    {
        return NULL;
    }
    lexer->fileStream = fileStream;
    return lexer;
}
