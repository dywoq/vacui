/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Main function of vqbuild utility
*/

#include "vqbconf.h"
#include "vqbcross.h"
#include "vqbrun.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

    const char       *dir = argv[1];
    std::stringstream config;
    config << dir << "/" << "config";
    std::string   config_str = config.str();
    std::ifstream file(config_str.c_str());
    if (!file.is_open())
    {
        std::cerr << "Failed to open \"" << config_str
                  << "\" configuration file" << std::endl;
        return 1;
    }

    try
    {
        vqbuild::compiler_set compiler_set =
            vqbuild::get_compiler_set(vqbuild::ARCHITECTURE_I386);
        vqbuild::run(compiler_set, dir);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
