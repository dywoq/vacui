#ifndef _KERNEL_H
#define _KERNEL_H

static void kernel() {
  asm("mov ah, 0Eh");
  asm("mov al, 'A'");
  asm("int 0x10");
  while (1) {
  }
}

#endif
