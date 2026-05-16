; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

org 0x8000
bits 16

; Contains the primary stage code of bootloader, which enables protected mode
; and jumps to the main installer point.

PreStartup:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    mov ax, 0x03
    int 0x10

    mov si, GREETING_MSG
    call PrintStr

    ; Enable A20 gate
    in al, 0x92
    or al, 2
    out 0x92, al

    mov ah, 0x42
    mov dl, 0x80
    mov si, InstallerDap
    int 0x13
    jc .diskError

    ; Enable protected mode and jump to pm_start
    cli
    lgdt [GdtPtr]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 0x08:PmStart

    jmp .halt

.diskError:
    mov si, FAILED_TO_LOAD_KERNEL
    call PrintStr
.halt:
    hlt
    jmp .halt

%include "print.S"
%include "dap.S"

GREETING_MSG db '* Vacui VQ 1.0 installer | Copyright 2026 dywoq - Apache License 2.0', 13, 10, 13, 10, 0
FAILED_TO_LOAD_KERNEL db 'ERROR: Failed to load installer', 13, 10, 0

bits 32
%include "gdt.S"
PmStart:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000

    jmp 0x10000
