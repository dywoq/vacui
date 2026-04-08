/* Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui */

ENTRY(_start)

SECTIONS
{
        . = 0x80200000;

        .start : {
                KEEP(*(.start))
        }

        .text : {
                *(.text .text.*)
        }

        .rodata : { *(.rodata .rodata.*) }
        .data   : { *(.data .data.*) }

        .bss : {
                _bss_start = .;
                *(.bss .bss.*)
                *(COMMON)
                _bss_end = .;
        } 
 
        /DISCARD/ :
        {
                *(.eh_frame)
                *(.note.*)
                *(.comment)
        }
}

