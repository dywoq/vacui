// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

.section .start, "ax", @progbits
.code16
.extern stage_two
.globl _start

_start:
    // Disable interrupts and setup code segments
    // and stack pointer
    cli
    xorw %ax, %ax
    movw %ax, %es
    movw %ax, %ds
    movw %ax, %ss
    movw $0x7bff, %ax
    movw %ax, %sp
    movl $0x7bff, %eax
    movl %eax, %esp
    sti

    // Jump to C-side
    call stage_two
