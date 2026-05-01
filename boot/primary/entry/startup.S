; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
; 
; Startup function of bootloader primary stage.
; Calls a entry function from C-side.

bits 16
section .start alloc exec
global startup
extern entry

db 'VQ'

startup:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    mov esp, 0x7bff
    sti

    call entry
