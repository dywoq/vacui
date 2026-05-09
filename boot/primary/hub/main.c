// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/primary/bios.h>
#include <vacui/primary/hub.h>

__asm(".code16gcc");

void primary()
{
  struct bios_dpa kernel_dap = {
      .size = 16,
      .reserved = 0,
      .sections = 2,
      .offset = 0x1000,
      .segment = 0,
      .start = 1
  };

  bool ok = bios_disk_extread(&kernel_dap, 0x80);
  if (!ok) {
    hub_puts("Failed to load kernel\n\r");
    goto hlt;
  }

hlt:
  while (1)
    __asm volatile("hlt\n");
}
