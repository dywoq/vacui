/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of commands from vqbcmd.h
*/

#include "vqbcmd.h"
#include "vqbarg.h"
#include "vqbcross.h"
#include "vqbmng.h"
#include <iostream>

namespace vqbuild
{
    vqbuild::cmd_status_code cmd_build(
        const std::vector<vqbuild::arg> &arguments
    )
    {
        if (arguments.empty())
        {
            std::cerr << "build: No arguments provided" << std::endl;
            return vqbuild::CMD_STATUS_ERR;
        }

        /* Fill needed arguments */
        std::string dir;
        try
        {
            arg dir_argument = get_argument("dir", ARG_STR, arguments);
            dir = dir_argument.value.str;
        }
        catch (const std::exception &e)
        {
            std::cerr << "build: " << e.what() << std::endl;
            return vqbuild::CMD_STATUS_ERR;
        }

        /* Begin building process */
        try
        {
            vqbuild::compiler_set compiler_set =
                vqbuild::get_compiler_set(vqbuild::ARCHITECTURE_I386);
            vqbuild::run(compiler_set, dir);
        }
        catch (const std::exception &e)
        {
            std::cerr << "build: " << e.what() << std::endl;
            return vqbuild::CMD_STATUS_ERR;
        }

        return vqbuild::CMD_STATUS_OK;
    }
} // namespace vqbuild
