;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Routine Description
;
;       Startup routine of VQ Kernel 
;

bits 16
global Startup
section .startup

;
; Routine Description
;
;       Disables the interrupts temporarily, and initializes the segments 
;       and stack. Calls the StartupInitialize function.
;
Startup:

        cli
        xor ax, ax
        mov es, ax
        mov ds, ax
        mov ss, ax
        mov sp, 0x7bff
        sti

        call StartupInitialize

