; Copyright (c) 2026 dywoq
;
; This code is released under the MIT License.
; https://opensource.org/licenses/MIT
;
; Repository:
; https://github.com/dywoq/vacui

%ifndef _VACUI_BOOTLOADER_
%define _VACUI_BOOTLOADER_

bits 16
org 0x7c00

; Represents the bootloader, which setups stack, code segments
; and jumps to the kernel.
_start: 
    ; Temporarily disable interruptions to setup segments
    ; and stack.
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti
    
    ; Jump to kernel.
    jmp kernel

    hlt ; Never executed
    
%include "src/bootloader.asm"

; Fill 510 bytes and create boot signature
times 510-($-$$) db 0
dw 0xaa55

%endif