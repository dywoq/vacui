// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <std/types.h>

void vga_output_char(std_byte_t ch) {
    __asm__ volatile("movb %0, %%al\n\t"
                     "movb $0x0e, %%ah\n\t"
                     "int $0x10\n\t"
                     :
                     : "rn"(ch)
                     : "ax");
}

void vga_output_str(const char *str) {

    for (const char *p = str; *p != '\0'; ++p) {
        vga_output_char(*p);
    }
}