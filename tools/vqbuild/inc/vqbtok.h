/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Token struct definitions

*/

#ifndef _VQBTOK_H
#define _VQBTOK_H

#include <stddef.h>
#include <stdint.h>

/*
Description:

    A type alias for token kind
*/
typedef uint16_t VQBTOK_KIND;
#define VQBTOK_IDENT (VQBTOK_KIND)0    /* Identifier */
#define VQBTOK_DIGIT (VQBTOK_KIND)1    /* Digit */
#define VQBTOK_STR (VQBTOK_KIND)2      /* String */
#define VQBTOK_OPERATOR (VQBTOK_KIND)3 /* Operator */

/*
Description:

    Token struct position definition
*/
typedef struct _VQBTOK_POS
{
    size_t line;
    size_t column;
    size_t index;
} VQBTOK_POS;

/*
Description:

    Token struct definition with literal name and position
*/
typedef struct _VQBTOK
{
    char *literal;

    /* literal's length includes null-terminator  */
    size_t literalLength;
    VQBTOK_KIND kind;
    VQBTOK_POS position;
} VQBTOK;

/*
Description:

    Allocates token struct instance and returns it, copying the provided values
    to instance.

    Returns null if the function:
    - failed to allocate token

    Returns instance with null literal if the function:
    - failed to allocate buffer to copy provided  literal
    - failed to copy provided literal

Parameters:

    - literal: The literal to copy, which must be null-terminated.

    - position: Position of the token

    - kind: Token kind

*/
VQBTOK *
VqbCreateToken(
    const char *literal,
    VQBTOK_POS position,
    VQBTOK_KIND kind
);

/*
Description:

    Frees a pointer to VQBTOK instance.
    Returns if the pointer is already null

*/
void
VqbDestroyToken(VQBTOK *token);

#endif
