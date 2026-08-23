/*
        Copyright 2026 dywoq - Apache License 2.0
        https://github.com/dywoq/vacui

        Routine Description

                Linker script of VQ Kernel
*/

OUTPUT_ARCH(i386)
ENTRY(Startup)

SECTIONS
{
        . = 0x8000;

        .startup        : { KEEP(*(.startup)) }
        .text           : { *(.text) }
        .text.bios      : { *(.text.bios) }
        .rodata         : { *(.rodata) }
        .data           : { *(.data) }
        .bss            : { *(.bss) }

        /DISCARD/ :
        {
                *(.note*)
                *(.eh_frame*)
        }
}
