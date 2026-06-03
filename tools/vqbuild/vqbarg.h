/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Arguments management and parsing
*/

#ifndef _VQBARG_H
#define _VQBARG_H

#include <stdint.h>
#include <string>
#include <vector>

namespace vqbuild
{
    /*
    Description:

        Standard argument exception class
    */
    class arg_exception : public std::exception
    {
      private:
        std::string msg_;

      public:
        explicit arg_exception(const std::string &msg);
        virtual ~arg_exception() throw();
        virtual const char *what() const throw();
    };

    /*
    Description:

        Enumeration argument types
    */
    enum arg_type : uint8_t
    {
        ARG_BOOL = 0,
        ARG_INT,
        ARG_STR
    };

    /*
    Description:

        Union with argument values
    */
    union arg_value {
        bool        b;
        int         i;
        const char *str;
    };

    /*
    Description:

        Structure with argument information.
        It's passed with other arzguments from parse_args.
    */
    struct arg
    {
        std::string name;
        arg_type    type;
        arg_value   value;
    };

    /*
    Description:

        Returns a dynamic list of parsed arguments from OS arguments (argv).
        The argument must be in this form:

            -<name>=<value>

        If one of strings doesn't start with -, the function skips it.

    Exceptions:
        vqbuild::arg_exception:
        - If argc is negative
        - If argv is null
        - If it failed to parse argument value
        - If '-' symbol is not in the start of string
    */
    std::vector<arg> parse_args(
        int   argc,
        char *argv[]
    );

    /*
    Description:

        Checks whether the argument present with provided name and type
	in given arguments list.

	Immediately returns false if arguments list is empty
    */
    bool is_argument_present(
        const std::string &name,
        arg_type           type,
	const std::vector<arg> &arguments
    );
} // namespace vqbuild

#endif
