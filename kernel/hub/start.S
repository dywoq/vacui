// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

.section .text
.global _start

_start:
    cli
    mov %cx, %ax
    mov %ax, %ds
    mov %ax, %es
    xor %ax, %ax
    mov %ax, %ss
    mov $0x8000, %ax
    mov %ax, %sp
    sti

    call hub
    