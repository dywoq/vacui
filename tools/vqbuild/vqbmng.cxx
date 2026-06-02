/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    An implementation of vqbmng.h
*/

#include "vqbmng.h"
#include "vqbconf.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace vqbuild
{

    /* run_exception config */
    run_exception::run_exception(const std::string &msg) : msg_(msg)
    {
    }
    run_exception::~run_exception() throw()
    {
    }
    const char *run_exception::what() const throw()
    {
        std::stringstream total_msg;
        total_msg << "vqbuild::run_exception: " << msg_;
        static std::string str = total_msg.str();
        return str.c_str();
    }

    static std::vector<std::string> from_str_to_vector_(const std::string &str)
    {
        std::vector<std::string> list;
        if (str.empty())
        {
            return list;
        }

        std::istringstream stream(str);
        std::string        token;

        while (std::getline(stream, token, ' '))
        {
            list.push_back(token);
        }
        return list;
    }

    static config parse_config_(const std::string &folder)
    {
        config            conf;
        std::stringstream config_path;
        config_path << folder << "/config";
        std::string config_path_str = config_path.str();
        const char *config_path_c_str = config_path_str.c_str();

        std::ifstream config_file(config_path_c_str);
        if (!config_file.is_open())
        {
            std::stringstream e_msg;
            e_msg << "Failed to open config file: " << config_path_c_str;
            throw run_exception(e_msg.str());
        }
        conf.parse(config_file);
        return conf;
    }

    static std::string gen_make_command_(
        const std::string   &folder,
        const compiler_set  &compiler_set,
        const config_values &conf_values
    )
    {
        std::stringstream cmd;

        cmd << "make " << "-C " << folder;

        /* Put compiler set options */
        cmd << " CC=\"" << compiler_set.cc << "\"";
        cmd << " CXX=\"" << compiler_set.cxx << "\"";
        cmd << " LINKER=\"" << compiler_set.linker << "\"";
        cmd << " AR=\"" << compiler_set.ar << "\"";

        /* Put config values */
        cmd << " TARGET=\"" << conf_values.target << "\"";
        cmd << " SOURCES=\"" << conf_values.sources << "\"";
        cmd << " OBJECTS_DIR=\"" << conf_values.objects_dir << "\"";
        cmd << " BUILD_DIR=\"" << conf_values.build_dir << "\"";
        cmd << " DEPENDENCIES=\"" << conf_values.dependencies << "\"";

        return cmd.str();
    }

    void run(
        const compiler_set &compiler_set,
        const std::string  &folder
    )
    {
        /* Parse configuration */
        config        conf = parse_config_(folder);
        config_values conf_values = conf.get_config_values();

        /* Get dependencies list and build them first recursively */
        std::vector<std::string> dependencies =
            from_str_to_vector_(conf_values.dependencies);
        if (!dependencies.empty())
        {
            std::vector<std::string>::const_iterator begin =
                dependencies.begin();
            std::vector<std::string>::const_iterator end = dependencies.end();
            while (begin != end)
            {
                std::stringstream total_folder;
                total_folder << folder << "/" << *begin;
                run(compiler_set, total_folder.str());
                begin++;
            }
        }

        /* Run Make command */
        std::string make_cmd =
            gen_make_command_(folder, compiler_set, conf_values);
        int code = std::system(make_cmd.c_str());
        if (code != 0)
        {
            std::stringstream e_msg;
            e_msg << "Failed to run command \"" << make_cmd
                  << "\" (code: " << code << ")";
            throw run_exception(e_msg.str());
        }
    }

} // namespace vqbuild
