/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Configuration struct definitions of vqbuild
*/

#ifndef _VQBCONF_H
#define _VQBCONF_H

#include <exception>
#include <fstream>
#include <map>
#include <string>

namespace vqbuild
{
    /*
    Description:

        Standard configuration exception class
    */
    class config_exception : public std::exception
    {
      private:
        std::string msg_;

      public:
        explicit config_exception(const std::string &msg) : msg_(msg)
        {
        }

        virtual ~config_exception() throw()
        {
        }

        virtual const char *what() const throw()
        {
            return msg_.c_str();
        }
    };

    /*
    Description:

        A configuration class. Responsible for parsing configuration file
        and reading its fields.
    */
    class config
    {
      private:
        std::map<std::string, std::string> keys_;
        bool                               parsed_;

        std::string trim_(const std::string &str)
        {
            size_t first = str.find_first_not_of(" \t\r\n");
            if (first == std::string::npos)
                return "";
            size_t last = str.find_last_not_of(" \t\r\n");
            return str.substr(first, (last - first + 1));
        }

      public:
        explicit config()
            : keys_(),
              parsed_(false)
        {
        }

        /*
        Description:

            Parses given file content, skipping comments (that start with #)
            and appends key and its value into underlying map.

            Skips the key if it's empty.
        */
        void parse(std::ifstream &file)
        {
            std::string line = "";
            while (std::getline(file, line))
            {
                line = trim_(line);
                if (line.empty() || line[0] == '#')
                {
                    continue;
                }

                size_t delimiter_pos = line.find('=');
                if (delimiter_pos == std::string::npos)
                    continue;

                std::string key = trim_(line.substr(0, delimiter_pos));
                std::string value = trim_(line.substr(delimiter_pos + 1));

                if (!key.empty())
                {
                    keys_[key] = value;
                }
            }
            parsed_ = true;
        }

        /*
        Description:

            Returns a value from SOURCES key.

        Exceptions:

            vqbuild::config_exception - If you didn't run parse function
        */
        std::string get_sources()
        {
            if (!parsed_)
                throw config_exception("parse() function is not ran");
            return keys_["SOURCES"];
        }

        /*
        Description:

            Returns a value from TARGET key.

        Exceptions:

            vqbuild::config_exception - If you didn't run parse function
        */
        std::string get_target()
        {
            if (!parsed_)
                throw config_exception("parse() function is not ran");
            return keys_["TARGET"];
        }

        /*
        Description:

            Returns a value from KIND key.

        Exceptions:

            vqbuild::config_exception - If you didn't run parse function
        */
        std::string get_kind()
        {
            if (!parsed_)
                throw config_exception("parse() function is not ran");
            return keys_["KIND"];
        }

        /*
        Description:

            Returns whether parse() command successfully or not.
        */
        bool parsed() const throw()
        {
            return parsed_;
        }
    };
} // namespace vqbuild

#endif
