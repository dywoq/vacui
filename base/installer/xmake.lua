-- Copyright 2026 dywoq - Apache License 2.0
-- https://github.com/dywoq/vacui

set_config("buildir", ".build")

function vqinstaller_add_module(folder)
    local include_dir = path.join(folder, "inc")
    local c_sources = path.join(folder, "**.c")
    local asm_sources = path.join(folder, "**.S")
    add_files(c_sources, {
        includedirs = include_dir
    })
    add_files(asm_sources)
end

toolchain("custom-gcc")
    set_kind("standalone")
    set_toolset("cc", "gcc")
    set_toolset("ld", "ld")
    set_toolset("as", "nasm")
toolchain_end()

option("vqinstaller_build_type")
    set_values("debug", "release")
    set_default("debug")
option_end()
function vqinstaller_setup_build_type()
    local val = get_config("vqinstaller_build_type")
    if not val then
        return
    end

    if val == "debug" then
        add_defines("DEBUG", { force = true })
    elseif val == "releese" then
        add_defines("RELEASE", { force = true })
    end
end

option("vqinstaller_val")
    set_values("vga_0x03")
    set_default("vga_0x03")
option_end()
function vqinstaller_setup_val()
    local val = get_config("vqinstaller_val")
    if not val then
        return
    end
    vqinstaller_add_module(path.join("val", val))
end

target("installer")
    set_toolchains("custom-gcc")
    add_cflags("-std=gnu23", "-fno-pie", "-fno-pic",
        "-Wextra", "-m32", "-fno-stack-protector",
        "-nostdlib", "-ffreestanding", "-I../inc/", "-Iinc", { force = true })
    add_ldflags("-T linker.ld", "-nostdlib", "-s",
        "--build-id=none", "-m", "elf_i386", "--gc-sections", { force = true })
    add_asflags("-f elf32", { force = true })

    vqinstaller_setup_build_type()
    vqinstaller_setup_val()

    vqinstaller_add_module("hub")
    vqinstaller_add_module("base")
target_end()
