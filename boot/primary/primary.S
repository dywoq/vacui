; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

org 0x8000
bits 16

; A primary bootloader is responsible for loading kernel and giving control to it.
; Before loading kernel, the primary bootloader gathers the boot information.

_start:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    ; We clear screen this way
    mov ax, 0x03
    int 0x10

    mov si, GREETING_MSG
    call print_str

    call get_kernel_mode
    call get_mm_map
    call get_vga_mode

    ; Enable A20 gate
    in al, 0x92
    or al, 2
    out 0x92, al

    mov ah, 0x42
    mov dl, 0x80
    mov si, kernel_dap
    int 0x13
    jc .disk_error

    ; Enable protected mode and jump to pm_start
    cli
    lgdt [gdt_ptr]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 0x08:pm_start
    
    jmp .halt
    
.disk_error:
    mov si, FAILED_TO_LOAD_KERNEL
    call print_str
.halt:
    hlt
    jmp .halt

%include "print.S"
%include "boot_info.S"
%include "dap.S"

GREETING_MSG db '   ---- By dywoq ---- | ----- Vacui 1.0 ----- | ----- Apache License 2.0 ----- ', 13, 10, 13, 10, 0
FAILED_TO_LOAD_KERNEL db 'ERROR: Failed to load kernel', 13, 10, 0

bits 32
%include "gdt.S"
pm_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000

    mov ebx, boot_info
    jmp 0x10000
