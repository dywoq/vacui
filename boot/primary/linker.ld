ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
        . = 0x8000;

        .start : {
                KEEP(*(.start))
        }
        
        .hub : {
                KEEP(*(.hub))
        }

        .text : {
                *(.text .text.*)
        }
        
        .bios : {
                KEEP(*(.bios))
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