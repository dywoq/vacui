ENTRY(startup)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
        . = 0x10000;
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
