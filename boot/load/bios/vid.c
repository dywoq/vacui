// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#include <vacui/abi/c.h>
#include <vacui/types.h>

__asm(".code16gcc");

VACUI_ABI_EXTERN_C
void
BiosTeletypePut(char character)
{
    __asm volatile("int $0x10\n" : : "a"(0x0E00 | character));
}

VACUI_ABI_EXTERN_C
void
BiosSwitchVidMode(UWord mode)
{
    __asm volatile("int $0x10\n" : : "a"(mode));
}

