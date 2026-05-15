-- Copyright 2026 dywoq - Apache License 2.0
-- https://github.com/dywoq/vacui

set_config("buildir", ".build")

function vac_add_module(folder)
    local sources = path.join(folder, "**.c")
    local asm_sources = path.join(folder, "**.S")
    local include_dir = path.join(folder, "inc")
    add_files(sources, { includedirs = include_dir })
    add_files(asm_sources)
end

toolchain("custom-gcc")
    set_kind("standalone")
    set_toolset("cc", "gcc")
    set_toolset("ld", "ld")
    set_toolset("as", "nasm")
toolchain_end()

target("kernel")
    set_toolchains("custom-gcc")
    add_cflags("--std=gnu23", "-fno-pie", "-fno-pic",
        "-Wextra", "-m32", "-fno-stack-protector",
        "-nostdlib", "-ffreestanding", "-Iinc/", { force = true })
    add_ldflags("-T linker.ld", "-nostdlib", "-s",
        "--build-id=none", "-m", "elf_i386", "--gc-sections", { force = true })
    add_asflags("-f elf32", { force = true })

    vac_add_module("base")
target_end()
