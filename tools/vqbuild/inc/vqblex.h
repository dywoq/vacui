/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Lexer struct definitions

*/

#ifndef _VQBLEX_H
#define _VQBLEX_H

#include <stdio.h>
#include <vqberr.h>

typedef struct _VQBLEX
{
    FILE *fileStream;
} VQBLEX;

/*
Description:

    Allocates and returns a pointer to VQBLEX struct instance.
    Returns null if it fails

Parameters:

    - fileStream: A pointer to file stream, stored in the struct 
    after allocation
    
*/
VQBLEX *
VqbCreateLexer(FILE *fileStream);

/*
Description:

    Frees a pointer to VQBLEX.

Notes:

    - fileStream parameters are not freed by the function

Parameters:

    - lexer: A pointer to VQBLEX to free
*/
void
VqbDestroyLexer(VQBLEX *lexer);

#endif
