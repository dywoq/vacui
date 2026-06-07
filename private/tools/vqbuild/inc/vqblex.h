/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Lexer class and token struct definition
*/

#ifndef _VQBLEX_H
#define _VQBLEX_H

#include <string>

namespace vqbuild
{
    enum token_kind
    {
        TOKEN_IDENTIFIER = 0,
        TOKEN_STRING,
        TOKEN_CHARACTER
    };

    struct token_position
    {
        int line;
        int index;
        int column;
    };

    struct token
    {
        std::string    literal;
        token_position position;
        token_kind     kind;

        explicit token(
            const std::string &new_literal,
            token_position     new_position,
            token_kind         new_kind
        );

        /*
        Description:

            Returns a string presentation of token.
        */
        const std::string str();
    };
} // namespace vqbuild

#endif
