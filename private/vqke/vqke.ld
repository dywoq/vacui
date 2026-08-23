OUTPUT_ARCH(i386)
ENTRY(BootEntry)

SECTIONS
{
        . = 0x8000;

        .startup        : { KEEP(*(.startup)) }
        .text           : { *(.text) }
        .rodata         : { *(.rodata) }
        .data           : { *(.data) }
        .bss            : { *(.bss) }

        /DISCARD/ :
        {
                *(.note*)
                *(.eh_frame*)
        }
}
