/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of vqbcross.h header

*/

#include "vqbcross.h"
#include <cstring>
#include <map>
#include <sstream>

namespace vqbuild
{

    compiler_set_exception::compiler_set_exception(const std::string &msg)
        : msg_(msg)
    {
    }
    compiler_set_exception::~compiler_set_exception() throw()
    {
    }
    const char *compiler_set_exception::what() const throw()
    {
        std::stringstream total_msg;
        total_msg << "vqbuild::compiler_set_exception: " << msg_;
        static std::string str = total_msg.str();
        return str.c_str();
    }

    /*
    Description:

        An underlying map with compiler sets
    */
    typedef std::map<architecture_t, compiler_set> compiler_sets_t_;
    static compiler_sets_t_                        compiler_sets_;
    static bool compiler_sets_initialized_ = false;

#define ARCH_LIST_COUNT_ 1
    static architecture_t arch_list_[ARCH_LIST_COUNT_] = {ARCHITECTURE_I386};

    bool is_architecture_correct(architecture_t arch)
    {
        for (size_t i = 0; i < ARCH_LIST_COUNT_; i++)
        {
            architecture_t arch_2 = arch_list_[i];
            if (arch == arch_2)
            {
                return true;
            }
        }
        return false;
    }

    /*
    Description:

        Lazily initializes compiler_sets_ map, which means it looks at
        compiler_sets_initialized_ flag and if it's false, the function begins
        initialization.
    */
    static void lazy_init_map_()
    {
        if (!compiler_sets_initialized_)
        {
            compiler_sets_ = compiler_sets_t_();
            compiler_sets_[ARCHITECTURE_I386] =
                (compiler_set){.cc = "gcc", .cxx = "g++", .linker = "ld"};
            compiler_sets_initialized_ = true;
        }
    }

    const compiler_set &get_compiler_set(architecture_t arch)
    {
        lazy_init_map_();
        compiler_sets_t_::iterator it = compiler_sets_.find(arch);
        if (it == compiler_sets_.end())
        {
            std::stringstream e_msg;
            e_msg << "Failed to find compiler set for \"" << arch
                  << "\" architecture";
            static std::string e_msg_str = e_msg.str();
            throw compiler_set_exception(e_msg_str);
        }
        return it->second;
    }
} // namespace vqbuild
