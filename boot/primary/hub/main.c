// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/primary/bios.h>
#include <vacui/primary/hub.h>

__asm(".code16gcc");

struct bios_dpa kernel_dap_ = {
    .size = 16,
    .reserved = 0,
    .sections = 2,
    .offset = 0x1000,
    .segment = 0x0,
    .start = 2,
};

struct bios_vbe_info vbe_info_ = {};

static void get_vbe_info()
{
        unsigned char status = 0;
        if (!bios_get_vbe(&vbe_info_, &status))
                hub_panic("Failed to get VBE info");
        hub_puts("Successfully got VBE info\n\r");
}

static void load_kernel()
{
        bool ok = bios_disk_extread(&kernel_dap_, 0x80);
        if (!ok && bios_disk_getstatus() != 0)
                hub_panic("Failed to load kernel");
        hub_puts("Successfully loaded kernel\n\r");
}

void primary()
{
        get_vbe_info();
        load_kernel();

        while (1)
                __asm volatile("hlt\n");
}
