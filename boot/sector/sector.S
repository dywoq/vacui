; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

org 0x7c00
bits 16

_start:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    mov ah, 0x42
    mov dl, 0x80
    mov si, primary_dap
    int 0x13
    jc .failed_to_load

    jmp 0x0800:0x0
.failed_to_load:
    mov si, FAILED_TO_LOAD_PRIMARY_STAGE
    call print_str
    jmp .halt
.halt:
    hlt
    jmp .halt

print_str:
.loop:
    cmp [si], 0
    je .return
    lodsb
    mov ah, 0x0e
    cmp al, 0
    jne .interrupt
    je .return
.interrupt:
    int 0x10
    jmp .loop
.return:
    ret

primary_dap:
    db 16
    db 0
    dw 2
    dw 0x0
    dw 0x0800
    dq 1

; Error messages
FAILED_TO_LOAD_PRIMARY_STAGE db 'Failed to load primary stage', 10, 13, 0

times 510-($-$$) db 0
dw 0xaa55
