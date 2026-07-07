-- Copyright 2026 dywoq - Apache License 2.0
-- https://github.com/dywoq/vacui

local conf = require "conf"
local conf_table, err = conf.parse("./VQBUILD")
if err ~= nil then 
    error("Failed to parse config: " .. err)
end
