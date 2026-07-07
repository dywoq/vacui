//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      An implementation of configuration exception class
//

#include <format>
#include <string>
#include <vqbconf.hxx>

namespace vqbuild::config
{
    ConfigException::ConfigException(const std::string &Message) noexcept
        : std::runtime_error(Message),
          Message_(Message)
    {
    }

    const char *
    ConfigException::what() const noexcept
    {
        static std::string FormattedMessage =
            std::format("vqbuild::config::ConfigException: {}", this->Message_);
        return FormattedMessage.c_str();
    }
} // namespace vqbuild::config
