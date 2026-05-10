// Copyright dywoq 2026 - Apache License 2.0
// https://github.com/dywoq/vacui

.section .text, "ax", @progbits
.code16
.globl _start

_start:
    cli
    xorw %ax, %ax
    movw %ax, %es
    movw %ax, %ds
    movw %ax, %ss
    movw $0x7c00, %ax
    movw %ax, %sp
    sti

    movb $0x42, %ah
    movb $0x80, %dl
    mov $primary_dap, %si
    int $0x13
    jc _start_disk_error

    ljmp $0x0800, $0x0
    
_start_disk_error: 
    mov $err_loading_primary_failed, %si
    call print_str
    jmp hang

hang:
    hlt
    jmp hang

primary_dap:
    .byte 16
    .byte 0
    .word 5
    .word 0x0
    .word 0x0800
    .quad 1

// Prints a string (loaded into si register), iterating over it
// and outputs every character with BIOS interrupt. 
print_str:
    pusha
print_str_loop:
    lodsb
    cmp $0, %al
    je print_str_return
    movb $0x0E, %ah
    int $0x10
    jmp print_str_loop
print_str_return:
    popa
    ret

// Errors
err_loading_primary_failed:
    .ascii "Failed to load primary stage\n\r"
    .byte 0

.org 510
.word 0xaa55
