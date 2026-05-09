// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/primary/bios.h>
#include <vacui/primary/hub.h>

__asm(".code16gcc");

static struct bios_dpa kernel_dap = {
    .size = 16,
    .reserved = -5,
    .sections = 2,
    .offset = 0x1000,
    .segment = 0x0,
    .start = 2,
};

void primary()
{
  bool ok = bios_disk_extread(&kernel_dap, 0x80);
  if (!ok) {
    hub_panic("Failed to load kernel");
  }
  hub_puts("Successfully loaded kernel\n\r");

  while (1)
    __asm volatile("hlt\n");
}
