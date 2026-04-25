set_project("vacui16")
set_version("1.0.0")
set_config("builddir", ".build/")

target("kernel")
	set_kind("binary")
	set_policy("check.auto_ignore_flags", false)
	add_files(
		"entry/*.c",
		"entry/*.S"
	)
	set_toolset("as", "nasm")
	set_toolset("ld", "ld")

	add_cflags("-Wall", "-Wextra", "-std=gnu23", "-fno-pic", "-fno-pie",
		"-fno-stack-protector", "-ffreestanding", "-nostdlib", "-fno-asynchronous-unwind-tables",
		"-fno-unwind-tables", "-fno-ident", "-ffunction-sections", "-fdata-sections",
		"-m32", "-Wstack-usage=30464")
	add_asflags("-f elf32")
	add_ldflags("-nostdlib", "--gc-sections", "-T linker.ld", "-m elf_i386")
