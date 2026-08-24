;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Routine Description
;
;       Provides printing functionality
;

;
; Routine Description
;
;       Iterates over the provided null-terminated string, using BIOS 
;       teletype interrupt to print string characters. 
;
;       Returns if si is null.
;
; Parameters
;
;       - si: A pointer to a string.
;
PrintString:
        cmp si, 0
        je .Loop
.Loop:
        je .Return
        lodsb
        cmp al, 0
        je .Return
        mov ah, 0x0E
        int 0x10
        jmp .Loop
.Return:
        ret

