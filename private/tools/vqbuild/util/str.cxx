/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        Implementation of string utility functions
*/

#include <vqbutilstr.h>

namespace vqbuild
{
    namespace util
    {
        void
        StrLeftTrim(
            std::string &string,
            const std::string &characterSet
        ) throw()
        {
            std::string::size_type start =
                string.find_first_not_of(characterSet);
            if (start != std::string::npos)
            {
                string.erase(0, start);
            }
            else
            {
                string.clear();
            }
        }

        void
        StrRightTrim(
            std::string &string,
            const std::string &characterSet
        ) throw()
        {
            std::string::size_type end = string.find_last_not_of(characterSet);
            if (end != std::string::npos)
            {
                string.erase(end + 1);
            }
            else
            {
                string.clear();
            }
        }

        void
        StrTrim(
            std::string &string,
            const std::string &characterSet
        ) throw()
        {
            StrLeftTrim(string, characterSet);
            StrRightTrim(string, characterSet);
        }
    } // namespace util
} // namespace vqbuild
