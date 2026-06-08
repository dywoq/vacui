; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
;
;       Kernel hub function
;

%ifndef _KE_HUB_S
%define _KE_HUB_S

KeHub:

    push bp
    mov bp, sp

    mov ah, 0x0e
    mov al, 'A'
    int 0x10

.loop:

    hlt
    jmp .loop

.return:

    pop bp
    ret

%endif
