//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//

#include <print>
#include <vqbconf.hxx>

int
main()
{
    vqbuild::config::ConfigMap ConfigA;
    ConfigA["TARGET"]  = "A";
    ConfigA["SOURCES"] = "B";

    vqbuild::config::ConfigMap ConfigB;
    ConfigB["TARGET"]  = "";
    ConfigB["SOURCES"] = "";

    if (vqbuild::config::ConfigMapsMatch(ConfigA, ConfigB))
    {
        std::println("Configuration maps match.");
    }
    else
    {
        std::println("Configuration maps do not match.");
    }

    return 0;
}
