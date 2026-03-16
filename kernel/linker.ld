/**
    Copyright 2026 dywoq - Apache License 2.0
    A part of https://github.com/dywoq/zero
**/

ENTRY(_start)
OUTPUT_FORMAT("binary")

SECTIONS {
    /* Set to 0 because we use segmented addressing 0x1000:0000 */
    . = 0x0;

    .text : {
        /* Force the entry code to the absolute beginning of the file */
        KEEP(*(.start))
        
        *(.text)
        *(.text.*)
        
        /* Include read-only data here for simpler 16-bit addressing */
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

    /* CRITICAL: Discard sections that cause "garbage" bytes in the binary */
    /DISCARD/ : {
        *(.note*)
        *(.indent)
        *(.comment)
        *(.eh_frame)
        *(.eh_frame_hdr)
        *(.debug*)
    }
}