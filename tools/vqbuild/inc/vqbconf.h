/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Config management, parsing and its type definitions

*/

#ifndef _VQBCONF_H
#define _VQBCONF_H

#include <exception>
#include <string>

namespace vqbuild
{
    namespace config
    {
        /*
        Description:

            Config field struct information in config fields map
        */
        struct ConfigFieldInfo
        {
            bool required;
            ConfigFieldInfo(bool required) throw();
        };

        /*
        Description:

            Exception class, thrown by config management functions

        */
        class ConfigException : public std::exception
        {
            std::string str_;

          public:
            virtual ~ConfigException() throw();
            ConfigException(const std::string &msg);
            ConfigException(const char *msg);

            const char *
            what() const throw();
        };
    } // namespace config
} // namespace vqbuild

#endif
