/**
    Copyright 2026 dywoq - Apache License 2.0
    A part of https://github.com/dywoq/zero
**/
ENTRY(_start)
OUTPUT_FORMAT("binary")

SECTIONS {
    . = 0x0;
    .start : { KEEP(*.(.start)) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
