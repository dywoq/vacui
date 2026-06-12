/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of destroy functions from vqblex.h

*/

#include <stdlib.h>
#include <vqblex.h>

void
VqbDestroyLexer(VQBLEX *lexer)
{
    if (!lexer)
    {
        return;
    }
    free(lexer);
    lexer = NULL;
}
