/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Main function of vqbuild utility
*/

#include "vqbconf.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main(
    int   argc,
    char *argv[]
)
{
    if (argc == 1)
    {
        std::cerr << "Specify directory in arguments, where you need to build "
                     "your target."
                  << std::endl;
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
        vqbuild::config conf;
        conf.parse(file);
        if (!conf.has_required_keys())
        {
            std::cerr
                << "Some of required keys in 'config' file are missing"
                << std::endl;
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
