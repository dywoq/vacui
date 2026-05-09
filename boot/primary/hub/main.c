// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <vacui/primary/bios.h>

void primary()
{
  while (1)
    __asm volatile("hlt\n");
}
