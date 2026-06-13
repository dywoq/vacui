/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of ConfigException

*/

#include <sstream>
#include <vqbconf.h>

namespace vqbuild
{
    namespace config
    {
        ConfigException::ConfigException(const std::string &msg) : str_(msg)
        {
        }

        ConfigException::ConfigException(const char *msg) : str_(msg)
        {
        }

        ConfigException::~ConfigException() throw()
        {
        }

        const char *
        ConfigException::what() const throw()
        {
            std::stringstream stream;
            stream << "vqbuild::config::ConfigException: "
                   << this->str_.c_str();
            static std::string str = stream.str();
            return str.c_str();
        }
    } // namespace config
} // namespace vqbuild
