ENTRY(startup)

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
