/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Commands struct declarations and management
*/

#ifndef _VQBCMD_H
#define _VQBCMD_H

#include "vqbarg.h"
#include <stdint.h>
#include <vector>

namespace vqbuild
{
    /*
    Description:

        Command handler status code. It's preferred over exceptions and system
        call exit for guaranteed cleanup of resources.
    */
    enum cmd_status_code : uint8_t
    {
        CMD_STATUS_OK = 0,
        CMD_STATUS_ERR,
    };

    /*
    Description:

        Command handler, which returns the status code and uses provided
        arguments.
    */
    typedef cmd_status_code (*cmd_handler_t)(const std::vector<arg> &arguments);

    /*
    Description:

        Command struct definition
    */
    struct cmd
    {
        std::string   name;
        cmd_handler_t handler;

        explicit cmd(
            std::string   new_name,
            cmd_handler_t handler
        )
            : name(new_name),
              handler(handler)
        {
        }
    };
} // namespace vqbuild

#endif
