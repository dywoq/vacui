/* Copyright 2026 dywoq - Apache License 2.0 */
/* A part of https://github.com/dywoq/zero */

OUTPUT_FORMAT("binary")
OUTPUT_ARCH(i386)
ENTRY(hub)

SECTIONS
{
    . = 0x10000;

    .text : {
        *(.text)
        *(.text.*)
    }

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }

    .data : {
        *(.data)
        *(.data.*)
    }

    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
}
