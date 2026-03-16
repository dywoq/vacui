-- Copyright 2026 dywoq - Apache License 2.0
-- A part of https://github.com/dywoq/lumen

local log = {}

local ansi_colors = {
    reset = "\27[0m",
    red = "\27[31m",
    yellow = "\27[33m",
    green = "\27[32m"
}

--- Prints a message into the console,
--- and automatically adds green `[info]` prefix to it.
---
--- @param v any The message to print.
function log.info(v)
    local prefix = ansi_colors.green .. "[info]" .. ansi_colors.reset
    print(prefix, " ", v)
end

--- Prints a message into the console,
--- and automatically adds yellow `[warn]` prefix to it.
--- 
--- @param v any The message to print.
function log.warn(v)
    local prefix = ansi_colors.yellow .. "[warn]" .. ansi_colors.reset
    print(prefix, " ", v)
end

--- Prints a message into the console,
--- and automatically adds red `[error]` prefix to it.
---
--- @param v any The message to print.
function log.error(v)
    local prefix = ansi_colors.red .. "[error]" .. ansi_colors.reset
    print(prefix, " ", v)
end

return log
