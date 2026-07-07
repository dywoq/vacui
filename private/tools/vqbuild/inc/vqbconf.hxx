//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      Configuration management
//

#ifndef _VQBCONF_HXX
#define _VQBCONF_HXX

#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>

namespace vqbuild::config
{
    //
    // Description:
    //
    //      Type definition for configuration map
    //
    using ConfigMap = std::unordered_map<std::string, std::string>;

    //
    // Description:
    //
    //      Class exception, thrown by the config management functionality
    //
    class ConfigException : public std::runtime_error
    {
        std::string Message_;

      public:
        explicit ConfigException(const std::string &Message) noexcept;

        const char *
        what() const noexcept override;
    };

    //
    // Description:
    //
    //      Configuration map parser
    //
    class ConfigParser
    {
      public:
        explicit ConfigParser() noexcept;

        //
        // Description:
        //
        //      Allocates a new file stream, and iterates over the
        //      file stream's lines.
        //
        //      The function skips the line if it's empty, or it
        //      contains hash.
        //
        //      The function finds an equal operator position, and constructs
        //      new sub-strings specifically for a config key and its value.
        //      If the config key value ends with backslash - the function
        //      enables a multi-line flag and skips the line, appending
        //      the value with no backslash to a final value buffer.
        //      If it doesn't - the function stores the key and
        //      the final value buffer into the map.
        //
        //      If the multi-line flag is still true in the start of loop,
        //      the function checks if the current line has backslash
        //      at the end. If it does - the function removes backslash
        //      and appends this line to the buffer. If it doesn't -
        //      the multi-line flag is disabled, the config key & the final
        //      value buffer are stored into the map, and the function
        //      resets conditions.
        //
        // Parameters:
        //
        //      - FilePath: A configuration file path
        //
        // Exceptions:
        //
        //
        //          -- vqbuild::config::ConfigException --
        //
        //      This exception is thrown by the function if:
        //      - the function failed to allocate file stream;
        //      - one of file's lines length is less than 3;
        //      - the function failed to find equal operator position;
        //      - equal operator position is in the start or in the end
        //      of file;
        //      - a config key name string is empty after trimming the line.
        //
        ConfigMap
        Parse(std::string_view FilePath);
    };
} // namespace vqbuild::config

#endif
