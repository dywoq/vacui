; Copyright 2026 dywoq - Apache License 2.0;
; A part of https://github.com/dywoq/vacui

bits 16 
section .start 
global Start 
extern Hub 

Start: 
        cli 
        xor ax, ax 
        mov es, ax 
        mov ds, ax 
        mov ss, ax 
        mov sp, 0x7BFF
        mov esp, 0x7BFF
        sti 

        call Hub
