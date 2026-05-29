/* Copyright 2026 dywoq - Apache License 2.0 */
/* A part of https://github.com/dywoq/zero */

OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0x8000;

    .start : {
        KEEP(*(.start .start.*))
    }

    .text : {
        *(.text .text.*)
    }

    .gdt : {
        KEEP(*(.gdt))
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
