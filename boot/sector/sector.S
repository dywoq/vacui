; Copyright 2026 dywoq - Apache License 2.0;
; A part of https://github.com/dywoq/vacui

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
        mov si, load_dap
        mov dl, 0x80
        int 0x13
        jc .disk_error
        
        jmp 0x0800:0x0
.disk_error:
        mov si, ERROR_DISK_ERROR_FAILED_GETTING_LOAD_STAGE
        call print_str
        jmp .loop
.loop:
        hlt
        jmp .loop

%include "print.S"

; Error messages
ERROR_DISK_ERROR_FAILED_GETTING_LOAD_STAGE:
        db "DISK ERROR: Failed to get 'Load stage'", 0

; The disk address pockets.
load_dap:
        db 16
        db 0
        dw 2
        dw 0x0
        dw 0x0800
        dq 1

times 510-($-$$) db 0
dw 0xaa55

