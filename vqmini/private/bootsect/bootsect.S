; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui

bits 16
org 0x7c00

; Description:
;
;       Startup of boot sector
BtSector:

    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    ;
    ; Save drive number
    ;
    mov [DriveNumber], dl

    ;
    ; Load kernel
    ;
    mov ah, 0x42
    mov si, KernelDap
    int 0x13
    jc .failedToLoadKernel

    ;
    ; Provide drive number and perform far jump
    ;
    mov dl, [DriveNumber]
    jmp 0x1000:0x0

.failedToLoadKernel:

    ; Change video mode in a case if it was changed
    int 0x10
    mov si, ErrFailedToLoadKernel
    call PrintStr
    jmp .halt

.halt:
    hlt
    jmp .halt

; Description:
;
;       Iterates over string, printing every character.
;       Returns if provided string is null.
;
; Parameters:
;
;       - SI: A string to iterate and print. Must be null-terminated
;       to avoid conflicting with foreign memory.
;
PrintStr:
.loop:
    cmp [si], 0
    je .return
    lodsb
    cmp al, 0
    je .return
    mov ah, 0x0e
    int 0x10
    jmp .loop
    
.return:
    ret

; Description:
;
;       Drive number data
DriveNumber:

    db 0

; Description:
;
;       Disk Address Packet for kernel
KernelDap:

    db 16       ; Size
    db 0        ; Reserved
    dw 2        ; Sectors count
    dw 0x0      ; Offset
    dw 0x1000   ; Segment
    dq 128      ; LBA Start

; Error messages
ErrFailedToLoadKernel db 'vqmini: Failed to lsoad kernel', 13, 10, 0

times 510-($-$$) db 0
dw 0xaa55
