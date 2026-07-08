-- 
-- Copyright 2026 dywoq - Apache License 2.0
-- https://github.com/dywoq/vacui
--
-- Description:
--
--      Makefile commands generation and management
-- 

local m = {}

--- Generates and returns a Make command with converted parameters,
--- specified Makefile rule and additional arguments.
---
--- @param params_table table<string, string>
--- @param rule string
--- @param additional_args string
--- @return string
function m.generate_make_command(params_table, rule, additional_args)
    local make_cmd = "make"
    local make_args = ""

    -- 
    -- Convert parameters table into string, appending it 
    -- to make_args.
    --
    for key, value in pairs(params_table) do
        local str = string.format('%s="%s"', key, value)
        make_args = make_args .. " " .. str
    end

    -- 
    -- Append arguments and Makefile rule and return it
    --
    make_cmd = make_cmd .. " " .. rule .. " " .. make_args .. " " .. additional_args
    return make_cmd
end

return m
