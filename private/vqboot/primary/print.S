;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;       This assembly file contains a printing functionality.
;

%ifndef _PRINT_S
%define _PRINT_S

;
; Description:
;
;       Iterates over a null-terminated array, printing every ASCII character
;       with BIOS interrupt.
;
; Parameters:
;
;       - si: A physical address of the null-terminated array of 
;       ASCII characters
;
PrintStr:
        
        .loop:
        cmp [si], 0
        je .return
        lodsb
        cmp al, 0
        je .return
        mov ah, 0x0E
        int 0x10
        jmp .loop

        .return:
        ret

%endif

