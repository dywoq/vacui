/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Token struct definitions

*/

#include <stdlib.h>
#include <vqbtok.h>

void
VqbDestroyToken(VQBTOK *token)
{
    if (!token)
    {
        return;
    }

    if (token->literal)
    {
        free(token->literal);
    }

    free(token);
    token = NULL;
}
