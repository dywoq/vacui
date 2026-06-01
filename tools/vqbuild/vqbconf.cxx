/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of vqbconf.h header
*/

#include "vqbconf.h"
#include <fstream>
#include <sstream>

namespace vqbuild
{
    /* config_exception class */
    config_exception::config_exception(const std::string &msg) : msg_(msg)
    {
    }
    config_exception::~config_exception() throw()
    {
    }
    const char *config_exception::what() const throw()
    {
        std::stringstream total_msg;
        total_msg << "vqbuild::config_exception: " << msg_;
        static std::string str = total_msg.str();
        return str.c_str();
    }

    /* config class */
    config::config()
        : keys_(),
          parsed_(false)
    {
    }

    void config::parse(std::ifstream &file)
    {
        std::string line = "";
        std::string accumulated_line = "";
        while (std::getline(file, line))
        {
            line = trim_(line);
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            if (line[line.length() - 1] == '\\')
            {
                std::string stripped_line =
                    trim_(line.substr(0, line.length() - 1));
                accumulated_line += stripped_line;
                accumulated_line += " ";
                continue;
            }
            else
            {
                accumulated_line += line;
            }

            size_t delimiter_pos = accumulated_line.find('=');
            if (delimiter_pos == std::string::npos)
            {
                accumulated_line = "";
                continue;
            }

            std::string key = trim_(accumulated_line.substr(0, delimiter_pos));
            std::string value =
                trim_(accumulated_line.substr(delimiter_pos + 1));

            if (!key.empty())
            {
                keys_[key] = value;
                accumulated_line = "";
            }
        }
        parsed_ = true;
    }

    std::string config::get_sources()
    {
        if (!parsed_)
            throw config_exception("parse() function is not ran");
        return keys_["SOURCES"];
    }

    std::string config::get_target()
    {
        if (!parsed_)
            throw config_exception("parse() function is not ran");
        return keys_["TARGET"];
    }

    std::string config::get_kind()
    {
        if (!parsed_)
            throw config_exception("parse() function is not ran");
        return keys_["KIND"];
    }

    bool config::parsed() const throw()
    {
        return parsed_;
    }
} // namespace vqbuild
