; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
;
;       Vacui VQ Mini startup code
;

bits 16
org 0x10000

Startup:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff ; ~30 KiB
    sti
    
    call KeHub  

%include "ke/hub.S"
