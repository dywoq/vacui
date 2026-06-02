/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Main function of vqbuild utility
*/

#include "vqbarg.h"
#include "vqbcmd.h"
#include <cstddef>
#include <iostream>
#include <vector>

static void print_usage_()
{
    std::cerr << "Usage: " << std::endl;
    std::cerr << "  vqbuild [command] [arguments...]" << std::endl;
}

static void print_info_()
{
    std::cerr << std::endl
              << "The vqbuild - is a C/C++ build orchestrator, made "
                 "specifically for Vacui codebase. "
              << std::endl;
    std::cerr << "Copyright 2026 dywoq - Apache License 2.0" << std::endl;
    std::cerr << "https://github.com/dywoq/vacui" << std::endl;
}

int main(
    int   argc,
    char *argv[]
)
{
    if (argc == 1)
    {
        print_usage_();
        print_info_();
        return 1;
    }

    /* Initialize commands array */
    std::vector<vqbuild::cmd> cmds;
    cmds.push_back(vqbuild::cmd("build", vqbuild::cmd_build));

    /* Find the given command, and output error if it's wrong */
    std::string                               given_cmd = argv[1];
    std::vector<vqbuild::cmd>::const_iterator begin = cmds.begin();
    std::vector<vqbuild::cmd>::const_iterator end = cmds.end();
    vqbuild::cmd                              found_cmd("", NULL);
    bool                                      ok = false;
    while (begin != end)
    {
        if (begin->name == given_cmd)
        {
            ok = true;
            found_cmd = *begin;
            break;
        }
        begin++;
    }
    if (!ok)
    {
        std::cerr << "Failed to find command with \"" << given_cmd << "\" name"
                  << std::endl;
        return 1;
    }

    /* Parse arguments and run command with
        these parsed arguments */
    try
    {
        std::vector<vqbuild::arg> args = vqbuild::parse_args(argc, argv);
        vqbuild::cmd_status_code  status_code = found_cmd.handler(args);
        if (status_code == vqbuild::CMD_STATUS_ERR)
            std::cerr << given_cmd << ": Command failed" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
