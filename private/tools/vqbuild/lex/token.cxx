/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of token struct functions
*/

#include <sstream>
#include <vqblex.h>

namespace vqbuild
{

    token::token(
        const std::string &new_literal,
        token_position     new_position,
        token_kind         new_kind
    )
        : literal(new_literal),
          position(new_position),
          kind(new_kind)
    {
    }

    const std::string token::str()
    {
        std::stringstream total;
        total << this->literal << " (" << this->position.line << ":"
              << this->position.column
              << ", Index in string: " << this->position.index
              << ", Kind: " << this->kind << ")";
        return total.str();
    }

} // namespace vqbuild
