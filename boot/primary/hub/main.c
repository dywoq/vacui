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

#define VGA_MODES_STR_GRAPHICS_COUNT 5
#define VGA_MODES_STR_TEXT_COUNT 2
static const char *vga_modes_str_graphic_[VGA_MODES_STR_GRAPHICS_COUNT] = {
    "[1] 320x200 (16 colors)",  "[2] 640x200 (16 colors)",
    "[3] 640x350 (16 colors)",  "[4] 640x480 (16 colors)",
    "[5] 320x200 (256 colors)",
};
static const char *vga_modes_str_text_[VGA_MODES_STR_TEXT_COUNT] = {
    "[1] 40x25 (16 colors)", "[2] 80x25 (16 colors)"
};

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

static void print_vga_modes_ (const char **list, char list_count)
{
        for (char i = 0; i < list_count; i++) {
                const char *str = list[i];
                hub_puts ("     ");
                hub_puts (str);
                hub_puts ("\n\r");
        }
}

static void ask_for_vga_mode_normal_ ()
{
        char scan_code, ascii_char = 0;
        hub_puts ("Choose VGA mode for normal mode:\n\r");
        print_vga_modes_ (vga_modes_str_graphic_, VGA_MODES_STR_GRAPHICS_COUNT);
repeat:
        char index = 0;
        bios_get_keystroke (&scan_code, &ascii_char);
        switch (ascii_char) {
        case '1':
                boot_info_.video->vga_mode = BOOT_VGA_320X200_16_COLORS;
                index = 0;
                break;
        case '2':
                boot_info_.video->vga_mode = BOOT_VGA_640X200_16_COLORS;
                index = 1;
                break;
        case '3':
                boot_info_.video->vga_mode = BOOT_VGA_640X350_16_COLORS;
                index = 2;
                break;
        case '4':
                boot_info_.video->vga_mode = BOOT_VGA_640X480_16_COLORS;
                index = 3;
                break;
        case '5':
                index = 4;
                boot_info_.video->vga_mode = BOOT_VGA_320X200_256_COLORS;
                break;
        default:
                goto repeat;
        }
        hub_puts ("Chosen VGA mode: ");
        hub_puts (vga_modes_str_graphic_[index]);
        hub_puts ("\n\r");
}

static void ask_for_vga_mode_recovery_ ()
{
        char scan_code, ascii_char = 0;
        hub_puts ("Choose VGA mode for recovery mode:\n\r");
        print_vga_modes_ (vga_modes_str_text_, VGA_MODES_STR_TEXT_COUNT);
repeat:
        char index = 0;
        bios_get_keystroke (&scan_code, &ascii_char);
        switch (ascii_char) {
        case '1':
                boot_info_.video->vga_mode = BOOT_VGA_40X25_TEXT_16_COLORS;
                index = 0;
                break;
        case '2':
                boot_info_.video->vga_mode = BOOT_VGA_80X25_TEXT_16_COLORS;
                index = 1;
                break;
        default:
                goto repeat;
        }
        hub_puts ("Chosen VGA mode: ");
        hub_puts (vga_modes_str_text_[index]);
        hub_puts ("\n\r");
}

void primary ()
{
        ask_for_kernel_mode_();
        if (boot_info_.kernel_mode == BOOT_KERNEL_NORMAL)
                ask_for_vga_mode_normal_();
        else if (boot_info_.kernel_mode == BOOT_KERNEL_RECOVERY)
                ask_for_vga_mode_recovery_();
        bios_set_vid_mode (boot_info_.video->vga_mode);
        load_kernel_dap_();

        while (1)
                __asm volatile ("hlt\n");
}
