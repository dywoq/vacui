/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Main function of vqbuild utility
*/

#include "vqbconf.h"
#include "vqbrun.h"
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file("config");
    if (!file.is_open())
    {
        std::cerr << "Failed to open \"config\" file" << std::endl;
        return 1;
    }

    try
    {
        vqbuild::config conf;
        conf.parse(file);
        vqbuild::run(conf, "./");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
