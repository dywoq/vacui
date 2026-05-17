/* Copyright 2026 dywoq - Apache License 2.0 */
/* A part of https://github.com/dywoq/zero */

OUTPUT_ARCH(i386)
ENTRY(Startup)

SECTIONS
{
    . = 0x10000;

    .text : {
        KEEP(*(.start))
        *(.text .text.*)
    }

    .rodata : { *(.rodata .rodata.*) }
    .data   : { *(.data .data.*) }
    .bss    : { *(.bss .bss.* COMMON) }


    /DISCARD/ :
    {
        *(.eh_frame)
        *(.note.*)
        *(.comment)
    }
}
