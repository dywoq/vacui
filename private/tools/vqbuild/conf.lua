-- Copyright 2026 dywoq - Apache License 2.0
-- https://github.com/dywoq/vacui
--
-- Description:
--
--      Configuration management, such as parsing
--

local m = {}

local function trim_(s)
    return s:match("^%s*(.-)%s*$")
end

--- 
--- Parses a given config file at filepath, with support of multi-line values 
--- and # comments.
---
--- Returns an error message if:
--- - failed to find equal operator;
--- - unterminated multi-line value detected.
---
--- @param filepath string
--- @return table? config_table
--- @return string? errmsg
function m.parse(filepath)
    local table_map = {}

    local is_parsing_multiline = false
    local key_buf = ""
    local value_buf = ""
    local line_number = 1

    for line in io.lines(filepath) do
        do
            --
            -- Ignore line if it's a comment or empty
            --
            local trimmed = trim_(line)
            if #trimmed == 0 or trimmed:sub(1, 1) == "#" then
                goto next_line
            end

            --
            -- If the function is currently parsing the multi-line value -
            -- trim and append the current line to the value buffer.
            --
            -- If there's no backslash at the end of the line - disable the flag
            -- and store the final key and value into the map.
            --
            if is_parsing_multiline then
                local has_backslash = string.sub(trimmed, -1) == "\\"

                if has_backslash then
                    value_buf = value_buf .. " " .. trim_(string.sub(trimmed, 1, -2))
                    goto next_line
                end

                value_buf = value_buf .. " " .. trimmed
                table_map[key_buf] = trim_(value_buf)

                is_parsing_multiline = false
                key_buf = ""
                value_buf = ""

                goto next_line
            end

            --
            -- Find equal operator position
            --
            local equal_op_start = string.find(line, "=")
            if equal_op_start == nil then
                return nil, string.format(
                    "no equal operator found in %d line:\n\t%d | %s",
                    line_number,
                    line_number,
                    line
                )
            end

            --
            -- Select the strings for config key and value
            --
            key_buf = trim_(string.sub(line, 1, equal_op_start - 1))
            local partial_value = trim_(string.sub(line, equal_op_start + 1))

            --
            -- Check if string has backslash at the end.
            -- If it does - enable is_parsing_multiline flag,
            -- and remove backslash before appending to the main value buffer.
            --
            if string.sub(partial_value, -1) == "\\" then
                is_parsing_multiline = true
                value_buf = trim_(string.sub(partial_value, 1, -2))
                goto next_line
            end

            table_map[key_buf] = partial_value

            ::next_line::
        end

        line_number = line_number + 1
    end

    if is_parsing_multiline then
        return nil, string.format(
            "unterminated multiline value for key '%s'",
            key_buf
        )
    end

    return table_map, nil
end

return m
