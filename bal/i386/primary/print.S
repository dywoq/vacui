; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;   Contains the print functionality

%ifndef _PRINT_S
%define _PRINT_S

; Description:
;
;   Iterates over string and prints every character
;   until encountering null terminator, using teletype output.
;
;   Returns if si is null.
;
; Parameters:
;
;   - SI: A string. Must be null-terminated.
print_str:

.loop:
    cmp [si], 0
    je .return
    lodsb
    cmp al, 0
    je .return
    mov ah, 0x0e
    int 0x10
    je .loop
.return:
    ret

%endif
