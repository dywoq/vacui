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
        
%include "dap.S"
        
        ; Load kernel DAP
        mov ah, 0x42
        mov dl, 0x80
        mov si, kernel_dap
        int 0x13

        ; Setup GDT pointer to table
        cli
        lgdt [gdt_ptr]

        ; Set PE bit in CR0
        mov eax, cr0
        or al, 1
        mov cr0, eax

        ; Far jump to pm_main
        jmp 0x08:pm_start

        hlt

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

bits 16
%include "mem.S"

section .text
setup_boot_info:
        call boot_video_info_setup
        call boot_mem_setup
        ret

; Setups a boot video information, 
; calling bios interuption which changes video mode to 0x13.
;
; Registers (pushed/popped): bx, ax
boot_video_info_setup:
        ; Push used registers to stack
        push ax

        ; Set values
        mov word [boot_video_data], 0x13
        mov word [boot_video_data + 2], 320
        mov word [boot_video_data + 4], 200

        ; Change VGA mode to [boot_video_data]
        xor ah, ah
        mov ax, word [boot_video_data]
        int 0x10

        ; Pop used registers
        pop ax
        ret

section .data
boot_video_data:
    dw 0 ; VGA Mode 
    dw 0 ; Width
    dw 0 ; Height
    
boot_info:
    dd boot_video_data ; Video info
    dd boot_mem_map ; Memory map 
