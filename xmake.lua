set_project("vacui")
set_version("1.0.0 ")
set_config("builddir", ".build/")

function vac_add_module(module_path)
    local module_name = path.basename(module_path)
    add_includedirs(path.join(module_path, "include"))
    add_files(path.join(module_path, "**.c"))
    add_files(path.join(module_path, "**.S"))
end

target("vqboot_primary")
	set_kind("binary")
	set_policy("check.auto_ignore_flags", false)
	set_toolset("as", "nasm")
	set_toolset("ld", "ld")

	add_cflags("-Wall", "-Werror", "-std=gnu23", "-fno-pic", "-fno-pie",
		"-fno-stack-protector", "-ffreestanding", "-nostdlib", "-fno-asynchronous-unwind-tables",
		"-fno-unwind-tables", "-fno-ident", "-ffunction-sections", "-fdata-sections",
		"-m32", "-Wstack-usage=30464")
	add_asflags("-f elf32")
	add_ldflags("-nostdlib", "--gc-sections", "-T linker.ld", "-m elf_i386", "-no-warn-rwx-segments")

	vac_add_module("boot/primary/hub")

target("vqkrnl")
	set_kind("binary")
	set_policy("check.auto_ignore_flags", false)
	set_toolset("as", "nasm")
	set_toolset("ld", "ld")

	add_cflags("-Wall", "-Werror", "-std=gnu23", "-fno-pic", "-fno-pie",
		"-fno-stack-protector", "-ffreestanding", "-nostdlib", "-fno-asynchronous-unwind-tables",
		"-fno-unwind-tables", "-fno-ident", "-ffunction-sections", "-fdata-sections",
		"-m32", "-Wstack-usage=30464")
	add_asflags("-f elf32")
	add_ldflags("-nostdlib", "--gc-sections", "-T linker.ld", "-m elf_i386", "-no-warn-rwx-segments")
