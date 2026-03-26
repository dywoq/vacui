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
        mov si, load_dap
        int 0x13

        jmp 0x0800:0x0

load_dap:
        db 16
        db 0
        dw 3
        dw 0x0
        dw 0x0800
        dq 1

times 510-($-$$) db 0
dw 0xaa55

