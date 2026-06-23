/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        Startup code of vqbuild

*/

#include <vqbutilstr.h>
#include <iostream>

int
main()
{

    std::string str = " KEY=sdsdgs sdsd\n";
    vqbuild::util::StrTrim(str, " \n\t");
    std::cout << str << std::endl;

    return 0;
}
