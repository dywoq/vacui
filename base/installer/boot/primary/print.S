; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

%ifndef _PRINT_S
%define _PRINT_S

PrintStr:
.loop:
    cmp [si], 0
    je .return
    lodsb
    mov ah, 0x0e
    cmp al, 0
    jne .interrupt
    je .return
.interrupt:
    int 0x10
    jmp .loop
.return:
    ret
    
%endif
