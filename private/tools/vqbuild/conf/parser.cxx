//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      An implementation of configuration parser
//

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <format>
#include <fstream>

#include <string>
#include <vqbconf.hxx>

namespace vqbuild::config
{
    ConfigParser::ConfigParser() noexcept
    {
    }

    static void
    Trim_(std::string &String)
    {
        auto IsSpace = [](unsigned char ch) { return isspace(ch); };
        auto FirstIt = std::find_if_not(String.begin(), String.end(), IsSpace);
        String.erase(String.begin(), FirstIt);
        auto EndIt = std::find_if_not(String.rbegin(), String.rend(), IsSpace);
        String.erase(EndIt.base(), String.end());
    }

    ConfigMap
    ConfigParser::Parse(std::string_view FilePath)
    {
        ConfigMap FinalConfigMap = {};

        //
        // Open file, and throw exception if the operation failed
        //
        std::ifstream FileStream(FilePath.data());
        if (!FileStream.is_open())
        {
            throw ConfigException(
                std::format("Failed to open config file (\"{}\")", FilePath)
            );
        }

        std::string Line             = "";
        std::string FinalKeyStr      = "";
        std::string FinalValueStr    = "";
        bool IsParsingMultilineValue = false;

        while (std::getline(FileStream, Line))
        {
            //
            // Check the line's length
            //
            if (Line.empty())
            {
                continue;
            }

            //
            // If there's a hash in the line - skip the line.
            //
            if (Line.find_first_of('#') != std::string::npos)
            {
                continue;
            }

            //
            // MULTI-LINE VALUE EXCLUSIVELY
            //
            // Check if we're currently parsing multi-line value.
            // If it's true - append the line to the final value.
            //
            // If the line has no backslash, disable flag and
            // store a final configuration key + value into the final map along
            // with resetting the conditions.
            //
            if (IsParsingMultilineValue)
            {
                if (!Line.ends_with('\\'))
                {
                    Trim_(Line);
                    FinalValueStr += Line;
                    FinalConfigMap[FinalKeyStr] = FinalValueStr;
                    IsParsingMultilineValue     = false;
                    FinalKeyStr                 = "";
                    FinalValueStr               = "";
                    continue;
                }
                else
                {
                    Trim_(Line);
                    Line.pop_back();
                    FinalValueStr += Line + " ";
                    continue;
                }
            }

            if (Line.length() < 3)
            {
                throw ConfigException(
                    "Line's length must be at least 3 characters long"
                );
            }

            //
            // Find the equal operator position
            //
            std::size_t EqualOpPosition = Line.find('=');
            if (EqualOpPosition == 0 || EqualOpPosition == Line.length())
            {
                throw ConfigException(
                    "Equal operation position must be not at the start/end of "
                    "line"
                );
            }

            if (EqualOpPosition == std::string::npos)
            {
                throw ConfigException("No equal operator position detected\n");
            }

            //
            // Select and trim the configuration key/value string
            // If key string empty - an exception is thrown.
            //
            FinalKeyStr = Line.substr(0, EqualOpPosition);
            auto PartialValueStr =
                Line.substr(EqualOpPosition + 1, Line.length());
            Trim_(FinalKeyStr);
            Trim_(PartialValueStr);
            if (FinalKeyStr.empty()) {
                throw ConfigException("Config key string is empty");
            }

            //
            // MULTI-LINE VALUE EXCLUSIVELY
            //
            // Check if the value has backslash.
            // If it does - enable the flag, append the value to buffer,
            // and skip the line.
            //
            if (PartialValueStr.ends_with('\\'))
            {
                IsParsingMultilineValue = true;
                PartialValueStr.pop_back();
                FinalValueStr += PartialValueStr + " ";
                continue;
            }

            //
            // Put the config key and its value into the map
            //
            FinalValueStr               = PartialValueStr;
            FinalConfigMap[FinalKeyStr] = FinalValueStr;
            FinalKeyStr                 = "";
            FinalValueStr               = "";
        }

        return FinalConfigMap;
    }
} // namespace vqbuild::config
