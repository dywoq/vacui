/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Main function of vqbuild utility
*/

#include "vqbconf.h"
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file("CONFIG");
    if (!file.is_open())
    {
        std::cerr << "Failed to open CONFIG file" << std::endl;
        return 1;
    }

    try
    {
        vqbuild::config conf;
        conf.parse(file);

        std::cout << "SOURCES: " << conf.get_sources() << std::endl;
        std::cout << "TARGET: " << conf.get_target() << std::endl;
        std::cout << "KIND: " << conf.get_kind() << std::endl;
    }
    catch (const vqbuild::config_exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
