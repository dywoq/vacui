// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

.section .start, "ax"
.code16gcc
.global _start
.extern hub

_start:
    cli
    xor %ax, %ax
    mov %ax, %es
    mov %ax, %ds
    mov %ax, %ss
    mov $0x7bff, %sp
    mov $0x7bff, %esp
    sti

    call hub
