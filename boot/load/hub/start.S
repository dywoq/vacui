// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

.code16
.section start
.global _start

_start:
        cli
        xor %ax, %ax
        movw %ax, %es
        movw %ax, %ds
        movw $0x0000, %ax
        movw %ax, %ss
        movw $0x8000, %ax
        movw %ax, %sp
        sti

        call hub

