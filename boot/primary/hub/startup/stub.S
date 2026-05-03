; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
;
; Stub assembly function, starts C-side startup function.

bits 16
section .start
extern startup
global stub

stub:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    mov esp, 0x7bff
    sti

    call startup
