; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
;
;       Hub entry function
;

%ifndef _HUB_ENTRY_S
%define _HUB_ENTRY_S

HubEntry:

    push bp
    mov bp, sp

    mov ah, 0x0e
    mov al, 'B'
    int 0x10

.loop:

    hlt
    jmp .loop

.return:

    pop bp
    ret

%endif
