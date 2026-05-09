// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

#include <vacui/primary/hub.h>

__asm(".code16gcc");

void primary()
{
  hub_put("Hi!\n\r");
  while (1)
    __asm volatile("hlt\n");
}
