;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Routine Description
;
;       Startup of the VQ Kernel engine in Assembly
;

bits 16
global Startup
extern KeInitialize

Startup:

    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    jmp KeInitialize
