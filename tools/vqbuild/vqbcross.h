/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Cross-compilation management

*/

#ifndef _VQBCROSS_H
#define _VQBCROSS_H

#include <string>

namespace vqbuild
{
    /*
    Description:

        Compiler set. It's filled by get_compiler_set
        and provided by it solely.
    */
    struct compiler_set
    {
        std::string cc;
        std::string cxx;
        std::string linker;
    };

    /*
    Description:

        Represents an enumeration architecture values.
    */
    enum architecture_t
    {
        ARCHITECTURE_I386 = 0,
    };

    /*
    Description:

        Standard compiler set management exception class
    */
    class compiler_set_exception : public std::exception
    {
      private:
        std::string msg_;

      public:
        explicit compiler_set_exception(const std::string &msg);
        virtual ~compiler_set_exception() throw();
        virtual const char *what() const throw();
    };

    /*
    Description:

        Checks if the given architecture is correct.
    */
    bool is_architecture_correct(architecture_t arch);

    /*
    Description:

        Returns compiler set, based on provided architecture value.

    Exceptions:

        vqbuild::compiler_set_exception - If it failed to find compiler set
        for the provided architecture
    */
    const compiler_set &get_compiler_set(architecture_t arch);
} // namespace vqbuild

#endif
