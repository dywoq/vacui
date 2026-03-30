// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

.code16
.section .start
.global _start
.extern entry

_start:
        cli
        xorw %ax, %ax
        movw %ax, %es
        movw %ax, %ds
        movw %ax, %ss
        movw $0x9000, %ax
        movw %ax, %sp
        sti

        call Entry
