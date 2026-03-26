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

        ; Block execution and ask for mode
        call block_and_ask_for_mode

        ; Setup boot info
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
%include "video.S"
%include "mode.S"

section .text
setup_boot_info:
        call boot_video_info_setup
        call boot_mem_setup
        ret

section .data
boot_info:
    dd boot_video_data ; Video info
    dd boot_mem_map ; Memory map
    dd boot_mode_info ; Mode info
