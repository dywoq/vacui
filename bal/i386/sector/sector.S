; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;   Contains the code of Boot Sector in BAL i386

org 0x7c00
bits 16

_start:

    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    mov [drive_number], dl
    
    mov ah, 0x42
    mov si, primary_dap
    int 0x13
    jc .disk_error

    jmp 0x8000:0x0

.disk_error:
    mov si, MSG_FAILED_TO_LOAD_PRIMARY_STAGE
    call print_str
    jmp .halt

.halt:
    hlt
    jmp .halt

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

; Description:
;   Disk Address Packet for primary bootloader stage
primary_dap:

    db 16
    db 0
    dw 2
    dw 0x0
    dw 0x8000
    dq 1

; Description:
;   Drive Number, which is was provided by BIOS into dl register
drive_number:

    db 0

; Messages
MSG_FAILED_TO_LOAD_PRIMARY_STAGE:

    db '[Vacui BAL i386] Failed to load bootloader primary stage'
    db 13
    db 10
    db 0

times 510-($-$$) db 0
dw 0xaa55
