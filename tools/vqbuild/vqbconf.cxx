/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of vqbconf.h header
*/

#include "vqbconf.h"
#include <fstream>
#include <map>
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
          parsed_(false),
          config_values_initialized_(false)
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

    bool config::parsed() const throw()
    {
        return parsed_;
    }

#define REQUIRED_KEYS_COUNT_ 5
    /*
    Description:

        Required keys table.
        Every time new field is added in config_values, you need to updated
        required keys table
    */
    static const char *required_keys_[REQUIRED_KEYS_COUNT_] = {
        "TARGET", "SOURCES", "OBJECTS_DIR", "BUILD_DIR", "DIRS"
    };

    bool config::has_required_keys()
    {
        if (!parsed_)
            throw config_exception("parse() function is not ran");
        using namespace std;
        map<std::string, std::string>::iterator end = keys_.end();
        for (size_t i = 0; i < REQUIRED_KEYS_COUNT_; i++)
        {
            map<std::string, std::string>::iterator val =
                keys_.find(required_keys_[i]);
            if (val == end)
                return false;
        }
        return true;
    }

    const config_values &config::get_config_values()
    {
        if (!parsed_)
            throw config_exception("parse() function is not ran");

        if (!has_required_keys())
            throw config_exception("config is missing required keys");

        if (!config_values_initialized_)
        {
            config_values_.target = keys_["TARGET"];
            config_values_.objects_dir = keys_["OBJECTS_DIR"];
            config_values_.sources = keys_["SOURCES"];
            config_values_.build_dir = keys_["BUILD_DIR"];
            config_values_.dependencies = keys_["DEPENDENCIES"];
            config_values_initialized_ = true;
        }

        return config_values_;
    }
} // namespace vqbuild
