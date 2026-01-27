#include <kernel.h>

asm("org 0x7c00");

void _start() {

    kernel();
}

asm("times 510-($-$$) db 0");
asm("dw 0xaa55");
