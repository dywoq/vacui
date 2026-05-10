// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

__asm (".code16gcc");

#include <vacui/primary/bios.h>
#include <vacui/primary/hub.h>

__hub void hub_puts (const char *str)
{
        for (const char *p = str; *p != '\0'; ++p)
                bios_tt_output (*p);
}
