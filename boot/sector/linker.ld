ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
        . = 0x7c00;

        .start : {
                KEEP(*(.start))
        }

        .text : {
                *(.text .text.*)
        }

        .pad : {
                KEEP(*(.pad))
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