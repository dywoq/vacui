/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Token struct definitions

*/

#include <stdlib.h>
#include <string.h>
#include <vqbtok.h>

VQBTOK *
VqbCreateToken(
    const char *literal,
    VQBTOK_POS position,
    VQBTOK_KIND kind
)
{
    VQBTOK *token = malloc(sizeof(VQBTOK));
    if (!token)
    {
        return NULL;
    }

    /* Fill position and kind */
    token->position = position;
    token->kind     = kind;

    /* Allocate buffer and copy literal */
    if (!literal)
    {
        token->literalLength = 0;
        return token;
    }
    size_t literalLength = strlen(literal) + 1;
    char *destBuffer     = malloc(literalLength);
    strncpy(destBuffer, literal, literalLength);
    token->literal       = destBuffer;
    token->literalLength = literalLength;

    return token;
}
