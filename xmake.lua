set_config("builddir", ".build/")

------------ Helper Functions ------------

--- Adds a module, including source files and include directory,
--- to the target in this form:
---
--- `-- <module>/`
---
--- `-- -- include/`
---
--- `-- -- **.c`
---
--- `-- -- **.S`
---
--- The source files are found recursively.
local function vac_module_add(module)
    add_includedirs(path.join(module, "include"))
    add_files(path.join(module, "**.c"))
    add_files(path.join(module, "**.S"))
end

------------ Toolchains ------------

--- RISC-V toolchain
toolchain("riscv64-elf-gcc")
    set_kind("standalone")
    set_toolset("cc", "riscv64-elf-gcc")
    set_toolset("cxx", "riscv64-elf-g++")
    set_toolset("ld", "riscv64-elf-ld")
    set_toolset("as", "riscv64-elf-gcc")
    set_toolset("objcopy", "riscv64-elf-objcopy")
    set_toolset("objdump", "riscv64-elf-objdump")
    add_ldflags("-m", "elf64lriscv", { force = true })
toolchain_end()

------------ Options ------------

option("vac_platform")
    set_default("qemu")
    set_values("qemu")
    set_description("Set the kernel platform")
option_end()

------------ Run checking ------------


target("vqkrnl")
    set_kind("binary")
    set_toolchains("riscv64-elf-gcc")

    add_cflags("-march=rv64gc", "-mabi=lp64d", "-mcmodel=medany", { force = true })
    add_asflags("-march=rv64gc", "-mabi=lp64d", { force = true })
    add_asflags("-march=rv64gc", "-mabi=lp64d", { force = true })

    add_cflags("-Wall", "-Werror", "-std=gnu23", "-fno-pic", "-fno-pie",
		"-fno-stack-protector", "-ffreestanding", "-nostdlib", "-fno-asynchronous-unwind-tables",
		"-fno-unwind-tables", "-fno-ident", "-ffunction-sections", "-fdata-sections",
		"-Wstack-usage=30464")

    add_ldflags("-nostdlib", "--gc-sections", "-T krnl/linker.ld", "-no-warn-rwx-segments", { force = true })

    if has_config("vac_platform", "qemu") then
        add_defines("PLATFORM_QEMU")
    end

    vac_module_add(string.format(path.join("krnl", "platform", "%s"), get_config("vac_platform")))
    vac_module_add(path.join("krnl", "hub"))
target_end()
