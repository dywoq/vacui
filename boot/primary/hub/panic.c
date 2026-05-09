// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <vacui/primary/bios.h>
#include <vacui/primary/hub.h>

[[noreturn]] __hub void hub_panic(const char *msg)
{
  bios_set_vid_mode(0x03);

  hub_puts("Vacui panics: ");
  hub_puts(msg);
  hub_puts("\n\r");

  hub_puts("Halting.\n\r");

  while (true)
    __asm volatile("hlt\n");
}
