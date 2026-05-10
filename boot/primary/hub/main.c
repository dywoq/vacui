// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/bootinfo.h>
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
struct boot_info boot_info_ = {};

static void init_vbe_info_()
{
        unsigned char status = 0;
        if (!bios_get_vbe(&vbe_info_, &status))
                hub_panic("Failed to get VBE info");
        if (vbe_info_.signature[0] != 'V' && vbe_info_.signature[1] != 'B' &&
            vbe_info_.signature[2] != 'E' && vbe_info_.signature[3] != '2')
                hub_panic("No 'VBE2' signature found in VBE information\n\r");
}

static void load_kernel_dap_()
{
        bool ok = bios_disk_extread(&kernel_dap_, 0x80);
        if (!ok && bios_disk_getstatus() != 0)
                hub_panic("Failed to load kernel with its Disk Address Packet");
}

static void ask_for_kernel_mode_()
{
        char scan_code, ascii_char = 0;
        hub_puts("Choose kernel mode (1 = Normal, 2 = Recovery): ");

repeat:
        bios_get_keystroke(&scan_code, &ascii_char);
        switch (ascii_char) {
        case '1':
                hub_puts("1\n\r");
                boot_info_.kernel_mode = BOOT_KERNEL_NORMAL;
                return;
        case '2':
                hub_puts("2\n\r");
                boot_info_.kernel_mode = BOOT_KERNEL_RECOVERY;
                return;
        default:
                goto repeat;
        }
}

void primary()
{
        ask_for_kernel_mode_();
        init_vbe_info_();
        load_kernel_dap_();

        while (1)
                __asm volatile("hlt\n");
}
