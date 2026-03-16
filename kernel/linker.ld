/**
    Copyright 2026 dywoq - Apache License 2.0
    A part of https://github.com/dywoq/zero
**/

ENTRY(_start)
OUTPUT_FORMAT("binary")

SECTIONS {
    . = 0x0;

    .text : {
        /* Force the entry code to the absolute beginning of the file */
        KEEP(*(.start))
        
        *(.text)
        *(.text.*)
        
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

    /DISCARD/ : {
        *(.note*)
        *(.indent)
        *(.comment)
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.debug*)
    }
}