// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm (".code16gcc");

#include <vacui/bootinfo.h>
#include <vacui/primary/bios.h>
#include <vacui/primary/hub.h>

struct bios_dpa kernel_dap_ = {
    .size = 16,
    .reserved = 0,
    .sections = 2,
    .offset = 0x1000,
    .segment = 0x0,
    .start = 2,
};

struct boot_info boot_info_ = {};

static void load_kernel_dap_ ()
{
        bool ok = bios_disk_extread (&kernel_dap_, 0x80);
        if (!ok && bios_disk_getstatus() != 0)
                hub_panic (
                    "Failed to load kernel with its Disk Address Packet"
                );
}

static void ask_for_kernel_mode_ ()
{
        char scan_code, ascii_char = 0;
        hub_puts ("Choose kernel mode (1 = Normal, 2 = Recovery): ");

repeat:
        bios_get_keystroke (&scan_code, &ascii_char);
        switch (ascii_char) {
        case '1':
                hub_puts ("1\n\r");
                boot_info_.kernel_mode = BOOT_KERNEL_NORMAL;
                return;
        case '2':
                hub_puts ("2\n\r");
                boot_info_.kernel_mode = BOOT_KERNEL_RECOVERY;
                return;
        default:
                goto repeat;
        }
}

void primary ()
{
        ask_for_kernel_mode_();
        load_kernel_dap_();

        while (1)
                __asm volatile ("hlt\n");
}
