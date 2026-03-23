; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

bits 16
org 0x8000

_start:
        cli
        xor ax, ax
        mov ds, ax
        mov es, ax
        mov ax, 0x0
        mov ss, ax
        mov sp, 0x8000
        sti

        call setup_boot_info

        ; Setup A20 gate
        in al, 0x92
        or al, 2
        out 0x92, al

        hlt

setup_boot_info:
        call setup_boot_video_info
        ret

; Setups a boot video information, 
; calling bios interuption which changes video mode to 0x13.
;
; Registers (pushed/popped): bx, ax
setup_boot_video_info:
        ; Push used registers to stack
        push bx
        push ax
        
        mov bx, boot_info + BootInfo.video
        mov word [bx + BootVideoInfo.mode], 0x13
        mov ax, word [bx + BootVideoInfo.mode]
        xor ah, ah
        int 0x10

        ; Change resolution
        mov word [bx + BootVideoInfo.width], 320
        mov word [bx + BootVideoInfo.height], 200

        ; Pop used registers
        pop ax
        pop bx
        ret

kernel_dap:
        db 16
        db 0
        dw 2
        dw 0x0
        dw 0x1000
        dq 2

section .bss
boot_info resb BootInfo_size

%include "boot.S"

