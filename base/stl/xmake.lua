set_config("buildir", ".build")

function vq_add_module(folder)
    local inc_dir = path.join(folder, "inc")
    add_includedirs(inc_dir)
end

function vq_add_sub_module(folder)
    local inc_dir = path.join(folder, "inc")
    local c_sources = path.join(folder, "**.c")
    local asm_sources = path.join(folder, "**.S")
    add_files(c_sources, { includedirs = inc_dir })
    add_files(asm_sources)
end

target("vqstl")
    set_kind("static")
    add_cflags("--std=gnu23", "-fno-pic", "-fno-pie", "-fno-stack-protector", "-nostdlib", "-ffreestanding")
    add_includedirs("inc", "../inc")

    vq_add_module("str")
    vq_add_sub_module(path.join("str", "len"))
target_end()
