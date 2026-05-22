// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

.code16gcc
.global _start

_start:
    cli
    xor %ax, %ax
    mov %ax, %es
    mov %ax, %ds
    mov %ax, %ss
    mov $0x7c00, %sp
    sti
    mov $0x42, %ah
    mov $primary_dap, %si
    int $0x10
    jc disk_error
    ljmp $0x0800, $0
disk_error:
    mov $ERR_FAILED_TO_LOAD_PRIMARY_STAGE, %si
    call print_str
    jmp halt
halt:
    hlt
    jmp halt

print_str:
print_loop:
    cmp $0, (%si)
    je print_ret
    lodsb
    cmp $0, %al
    je print_ret
    mov $0x0E, %ah
    int $0x10
    jmp print_loop
print_ret:
    ret

primary_dap:
    .byte 16
    .byte 0
    .word 2
    .word 0
    .word 0x0800
    .quad 1

// Error messages
ERR_FAILED_TO_LOAD_PRIMARY_STAGE:
    .ascii "BAL i386: Failed to load boot primary stage\n\r"
    .byte 0

.fill 510 - (. - _start), 1, 0
.word 0xaa55
