//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//

#include <exception>
#include <iostream>
#include <print>
#include <vqbconf.hxx>

int
main()
{
    try
    {
        vqbuild::config::ConfigParser ConfigParser;
        auto ConfigMap = ConfigParser.Parse("VQBUILD");
        for (const auto Value : ConfigMap)
        {
            std::println("Map[\"{}\"] = \"{}\"", Value.first, Value.second);
        }
    }
    catch (const std::exception &Error)
    {
        std::cout << Error.what() << std::endl;
    }

    return 0;
}
