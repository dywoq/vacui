-- Copyright 2026 dywoq - Apache License 2.0
-- A part of https://github.com/dywoq/lumen

local cmd = require("scripts.lib.cmd")
local log = require("scripts.lib.log")

-- =============================
--         Configuration
-- =============================

--- Checks whether environment variable BUILD_TYPE is defined.
--- If it is, it gets its value and validates it.
--- If value of BUILD_TYPE is wrong, the function prints an error
--- and exits the process.
---
--- If there's no BUILD_TYPE, the function returns the default value.
---
--- @return string build_type The default value is: "debug" or value of BUILD_TYPE.
local function get_and_validate_build_type()
    local build_type = "debug"
    local build_type_manual = false
    if os.getenv("BUILD_TYPE") then
        local res = os.getenv("BUILD_TYPE")
        build_type = res or "" -- It's meaningless to add or, but it's needed to calm down LSP
        build_type_manual = true
    end
    if build_type_manual then
        if build_type ~= "release" and build_type ~= "debug" then
            log.error("Wrong build type: " .. build_type .. ". Expected: release debug")
            os.exit(1)
        end
    end
    if not build_type_manual  then
        log.warn("Defaulting BUILD_TYPE to debug")
    end
    return build_type
end
local build_type = get_and_validate_build_type()

-- Temp directory
local build_temp = ".build"

-- =============================
--            Steps
-- =============================

-- Make build directory
log.info("Created temp directory")
cmd.run_and_fail("mkdir", { build_temp, "-p" })

-- Compile boot sector/kernel
log.info("Compiling boot sector/kernel")
cmd.run_and_fail("cd boot && make clean all", {})
cmd.run_and_fail("cd kernel &&" .. " BUILD_TYPE=" .. build_type .." make clean all", {})


-- Create .img file
log.info("Creating .img file")
local sector_bin = "boot/.build/sector.bin"
local kernel_bin = "kernel/.build/kernel.bin"
local img_file = build_temp .. "/zero.img"
cmd.run_and_fail("dd", { "if=/dev/zero", "of=" .. img_file, "bs=1M", "count=10" })
cmd.run_and_fail("dd", { "if=" .. sector_bin, "of=" .. img_file, "bs=512", "count=1", "conv=notrunc" })
cmd.run_and_fail("dd", { "if=" .. kernel_bin, "of=" .. img_file, "bs=512", "seek=1", "conv=notrunc"  })
log.info("Building .img file is done")
