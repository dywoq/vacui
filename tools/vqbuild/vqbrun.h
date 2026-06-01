/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:


*/

#ifndef _VQBRUN_H
#define _VQBRUN_H

#include "vqbconf.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>

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
        explicit run_exception(const std::string &msg) : msg_(msg)
        {
        }

        virtual ~run_exception() throw()
        {
        }

        virtual const char *what() const throw()
        {
            std::stringstream total_msg;
            total_msg << "vqbuild::run_exception: " << msg_;
            static std::string str = total_msg.str();
            return str.c_str();
        }
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
    )
    {
        if (!conf.parsed())
        {
            throw run_exception("config is not parsed");
        }

        if (folder.empty())
        {
            throw run_exception("folder path is empty");
        }

        std::string target = conf.get_target();
        std::string kind = conf.get_kind();
        std::string sources = conf.get_sources();

        if (target.empty() || kind.empty() || sources.empty())
        {
            throw run_exception("TARGET, KIND or SOURCES is empty");
        }

        std::stringstream makefile_cmd;
        makefile_cmd << "make " << "-C " << folder << " TARGET=\"" << target
                     << "\" KIND=\"" << kind << "\"" << " SOURCES=\"" << sources
                     << "\"";
        std::string makefile_cmd_str = makefile_cmd.str();

        int code = std::system(makefile_cmd_str.c_str());
        if (code < 0)
        {
            std::stringstream err_msg;
            err_msg << "Failed to run \"" << makefile_cmd_str.c_str()
                    << "\" command (exit code: " << code << ")";
            std::string err_msg_str = err_msg.str();
            const char *err_msg_c_str = err_msg_str.c_str();
            throw run_exception(err_msg_c_str);
        }
    }

} // namespace vqbuild

#endif
