/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of ConfigFieldInfo
*/

#include <vqbconf.h>

namespace vqbuild
{
    namespace config
    {
        ConfigFieldInfo::ConfigFieldInfo(bool required) throw()
            : required(required)
        {
        }
    } // namespace config
} // namespace vqbuild
