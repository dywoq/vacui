// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

.code16
.section .start
.global _start

_start:
    cli
    mov $0x1000, %ax
    mov %ax, %ds
    mov %ax, %es
    xor %ax, %ax
    mov %ax, %ss
    mov $0x8000, %ax
    mov %ax, %sp
    sti
    
    # Set Video Mode 0x13
    mov $0x0013, %ax
    int $0x10

    call hub
    
    # Hang if hub returns
loop:
    hlt
    jmp loop
