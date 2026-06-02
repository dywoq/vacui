/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of vqbarg.h
*/

#include "vqbarg.h"
#include <sstream>
#include <string>
#include <vector>

namespace vqbuild
{
    /* arg_exception */
    arg_exception::arg_exception(const std::string &msg) : msg_(msg)
    {
    }
    arg_exception::~arg_exception() throw()
    {
    }
    const char *arg_exception::what() const throw()
    {
        std::stringstream total_msg;
        total_msg << "vqbuild::arg_exception: " << msg_;
        static std::string str = total_msg.str();
        return str.c_str();
    }

    static void parse_arg_bool_(
        bool              &is_success,
        bool              &value,
        const std::string &value_str
    )
    {
        if (value_str == "true" || value_str == "T")
        {
            is_success = true;
            value = true;
            return;
        }
        else if (value_str == "false" || value_str == "F")
        {
            is_success = true;
            value = false;
            return;
        }
        is_success = false;
    }

    static void parse_arg_str_(
        bool              &is_success,
        const char       *&value,
        const std::string &value_str
    )
    {
        static std::vector<std::string> storage;
        storage.push_back(value_str);
        value = storage.back().c_str();
        is_success = true;
    }

    static void parse_arg_value_(
        const std::string &value_str,
        arg_value         &arg_value,
        arg_type          &arg_type
    )
    {
        if (value_str.empty())
            throw arg_exception("Argument value is empty");

        bool is_success = false;

        /* Parse boolean */
        {
            bool value = false;
            parse_arg_bool_(is_success, value, value_str);
            if (!is_success)
            {
                goto str;
            }
            arg_value.b = value;
            arg_type = ARG_BOOL;
            return;
        }

        /* Parse string */
    str: {
        const char *value = "";
        parse_arg_str_(is_success, value, value_str);
        arg_value.str = value;
        arg_type = ARG_STR;
        return;
    }

        std::stringstream e_msg;
        e_msg << "Failed to parse argument value: " << value_str;
        throw arg_exception(e_msg.str());
    }

    static std::string get_value_in_arg_str_(
        const std::string &arg_str,
        size_t             start_pos
    )
    {
        std::string                 value_str;
        std::string::const_iterator value_begin =
            arg_str.begin() + start_pos + 1;
        std::string::const_iterator arg_str_end = arg_str.end();
        while (value_begin != arg_str_end)
        {
            value_str += *value_begin;
            value_begin++;
        }
        return value_str;
    }

    static std::string get_name_in_arg_str_(
        const std::string &arg_str,
        size_t             start_pos
    )
    {
        std::string                 name;
        std::string::const_iterator name_begin =
            arg_str.begin() + start_pos + 1;
        while (*name_begin != '=')
        {
            name += *name_begin;
            name_begin++;
        }
        return name;
    }

    /*
    Description:

        Parses an argument, using the given argument string.
        If it detects it's not flag, it sets is_flag to false.

    Exceptions:

        vqbuild::arg_exception:
        - If it failed to find = operator
        - If it failed to parse argument value
    */
    static arg parse_arg_(
        bool              &is_flag,
        const std::string &arg_str
    )
    {
        arg argument = {};

        /* Get position of - and = symbols */
        size_t name_start_pos = arg_str.find('-');
        if (name_start_pos == arg_str.npos)
        {
            is_flag = false;
            return argument;
        }
        /* Must start be at start of string */
        if (name_start_pos != 0)
            throw arg_exception("'-' character is not in the start of string");

        size_t value_start_pos = arg_str.find('=');
        if (value_start_pos == arg_str.npos)
            throw arg_exception("no '=' character found in argument string");

        /* Get name and value */
        std::string name_str = get_name_in_arg_str_(arg_str, name_start_pos);
        std::string value_str = get_value_in_arg_str_(arg_str, value_start_pos);

        /* Parse argument value and get its type */
        parse_arg_value_(value_str, argument.value, argument.type);

        /* Fill any left information */
        is_flag = true;
        argument.name = name_str;

        return argument;
    }

    std::vector<arg> parse_args(
        int   argc,
        char *argv[]
    )
    {
        if (argc < 0)
            throw arg_exception("argc is negative");

        if (!argv)
            throw arg_exception("argv is null");

        std::vector<arg> args;
        if (argc == 1)
            return args;

        for (size_t i = 1; i < argc; i++)
        {
            std::string str(argv[i]);
            bool        is_flag = false;
            arg         argument = parse_arg_(is_flag, str);
            if (is_flag)
            {
                args.push_back(argument);
            }
        }

        return args;
    }
} // namespace vqbuild
