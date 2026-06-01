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
        explicit config_exception(const std::string &msg);
        virtual ~config_exception() throw();
        virtual const char *what() const throw();
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
        explicit config();

        /*
        Description:

            Parses given file content, skipping comments (that start with #)
            and appends key and its value into underlying map.

            Handles multi-line lists. To create multi-line list, use '\'
            character at the end of line to continue the list.

            Skips the key if it's empty.
        */
        void parse(std::ifstream &file);

        /*
        Description:

            Returns a value from SOURCES key.

        Exceptions:

            vqbuild::config_exception - If you didn't run parse function
        */
        std::string get_sources();

        /*
        Description:

            Returns a value from TARGET key.

        Exceptions:

            vqbuild::config_exception - If you didn't run parse function
        */
        std::string get_target();

        /*
        Description:

            Returns a value from KIND key.

        Exceptions:

            vqbuild::config_exception - If you didn't run parse function
        */
        std::string get_kind();

        /*
        Description:

            Returns whether parse() command successfully or not.
        */
        bool parsed() const throw();
    };
} // namespace vqbuild

#endif
