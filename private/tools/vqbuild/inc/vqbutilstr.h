/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        String utility functions
*/

#ifndef _VQBUTILSTR_H
#define _VQBUTILSTR_H

#include <string>

namespace vqbuild
{
    namespace util
    {
        void
        StrLeftTrim(
            std::string &string,
            const std::string &characterSet
        ) throw();
        void
        StrRightTrim(
            std::string &string,
            const std::string &characterSet
        ) throw();
        void
        StrTrim(
            std::string &string,
            const std::string &characterSet
        ) throw();
    } // namespace util
} // namespace vqbuild

#endif
