; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

bits 16
org 0x7c00

_start:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    mov ah, 0x42
    mov dl, 0x80
    mov si, kernel_dap
    int 0x13

    jmp 0x1000:0x0000
    
    hlt

kernel_dap:
    db 16 ; Size
    db 0 ; Reserved
    dw 1 ; How much sectors we read (1 sector = 512 bytes)
    dw 0x0000 ; Offset
    dw 0x1000 ; Segment
    dq 1 ; LBA start

; Fill 510 bytes and create signature
times 510-($-$$) db 0
dw 0xaa55
