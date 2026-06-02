/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of vqbrun.cxx
*/

#include "vqbrun.h"
#include "vqbconf.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

namespace vqbuild
{

    /* run_exception config */
    run_exception::run_exception(const std::string &msg) : msg_(msg)
    {
    }
    run_exception::~run_exception() throw()
    {
    }
    const char *run_exception::what() const throw()
    {
        std::stringstream total_msg;
        total_msg << "vqbuild::run_exception: " << msg_;
        static std::string str = total_msg.str();
        return str.c_str();
    }

    /* run method */
    void run(
        config             &conf,
        const compiler_set &compiler_set,
        const std::string  &folder
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

        const config_values &conf_vals = conf.get_config_values();

        std::stringstream makefile_cmd;
        makefile_cmd << "make " << "-C " << folder << " TARGET=\""
                     << conf_vals.target << "\"" << " SOURCES=\""
                     << conf_vals.sources << "\""
                     << " OBJECTS_DIR=\"" << conf_vals.objects_dir << "\""
                     << " BUILD_DIR=\"" << conf_vals.build_dir << "\"";
        makefile_cmd << " CC=\"" << compiler_set.cc << "\"" << " CXX=\""
                     << compiler_set.cxx << "\" LINKER=\""
                     << compiler_set.linker << "\"";
        std::string makefile_cmd_str = makefile_cmd.str();

        std::cout << makefile_cmd_str << std::endl;

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
