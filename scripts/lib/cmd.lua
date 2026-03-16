-- Copyright 2026 dywoq - Apache License 2.0
-- A part of https://github.com/dywoq/lumen

local cmd = {}

local log = require("scripts.lib.log")

--- Runs a command with given arguments.
--- If the command fails, the function prints its error code
--- and exits the process with code 1.
---
--- @param name string The command to run.
--- @param args table The command arguments.
function cmd.run_and_fail(name, args)
    local args_str = table.concat(args, " ")
    local total_cmd = string.format("%s %s", name, args_str)
    local ok, exitcode, code = os.execute(total_cmd)

    if ok then return end

    local reason = ""
    if exitcode == "exit" then
        reason = "EXIT"
    elseif exitcode == "signal" then
        reason = "SIGNAL"
    end

    local total_msg = string.format('Failed to execute "%s" command (%s). Exit code: %d', total_cmd, reason, code)
    log.error(total_msg)
    os.exit(1)
end

return cmd
