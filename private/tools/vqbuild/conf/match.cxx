//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      An implementation of match functions
//

#include <vqbconf.hxx>

namespace vqbuild::config
{
    bool
    ConfigMapsMatch(
        ConfigMap ConfigA,
        ConfigMap ConfigB
    ) noexcept
    {
        for (const auto &[key, value] : ConfigA)
        {
            if (!ConfigB.contains(key))
            {
                return false;
            }
        }
        return true;
    }
} // namespace vqbuild::config
