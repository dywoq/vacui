/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Contains functionality for managing Makefiles with configuration
*/

#ifndef _VQBMNG_H
#define _VQBMNG_H

#include "vqbcross.h"
#include <exception>
#include <string>

namespace vqbuild
{
    /*
    Description:

        Standard exception class, which is thrown by run functions
    */
    class run_exception : public std::exception
    {
      private:
        std::string msg_;

      public:
        explicit run_exception(const std::string &msg);
        virtual ~run_exception() throw();

        virtual const char *what() const throw();
    };

    void run(
        const compiler_set &compiler_set,
        const std::string  &folder
    );
} // namespace vqbuild

#endif
