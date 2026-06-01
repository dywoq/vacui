/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Contains functionality for running Makefiles with configuration
*/

#ifndef _VQBRUN_H
#define _VQBRUN_H

#include "vqbconf.h"

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

    /*
    Description:

        Runs a Makefile in the given folder path, using the configuration
        values.

    Exceptions:

        vqbuild::run_exception:
        - If SOURCES, TARGET or KIND string is empty
        - If configuration is not parsed
        - If it failed to run Makefile
        - If folder path is empty
    */
    void run(
        config            &conf,
        const std::string &folder
    );
} // namespace vqbuild

#endif
