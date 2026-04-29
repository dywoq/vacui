; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Module description:
;   The assembly stub start file of kernel.
;
;   It's put in '.start' section so the hardware 
;   couldn't start random function.
;

bits 16
section .start
global startup
extern hub

startup:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    mov esp, 0x7bff
    sti

    call hub

    ret
