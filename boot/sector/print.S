; Copyright 2026 dywoq - Apache License 2.0;
; A part of https://github.com/dywoq/vacui

%ifndef _PRINT_S
%define _PRINT_S

; Description:
;       Prints a message into the screen, using BIOS interrupt, 
;       following the form:
;               * ah  = 0x0e
;               * al  = <current iterated character>
;               * int = 0x10
;       
;       Loads a character into the memory and increments pointer,
;       iterating over string.
;
; Parameters:
;      * si: A pointer to string.
print_str:
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

