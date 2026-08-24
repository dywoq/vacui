;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Module Description
;
;       VQBoot sector stage code
;

bits 16
global SectorEntry

section .entry
SectorEntry:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    ;
    ; Save the drive number
    ;
    mov [DriveNumber], dl
    
.LoadPrimaryStage:
    mov ah, 0x42
    mov si, PrimaryStageDap
    int 0x13
    jc .DiskError
    jnc .ExecutePrimaryStage
.DiskError:
    mov si, Message_LoadingPrimaryStageFailed
    call PrintString
    jmp .Halt
.Halt:
    hlt
    jmp .Halt
.ExecutePrimaryStage:
    ;
    ; Provide the drive number, saved earlier 
    ;
    mov dl, [DriveNumber] 
    jmp 0x0800:0x0000

;
; Description
;
;       Iterates over the string characters and prints them. Returns if 
;       AL register is 0 or DS:SI is 0.
;
; Arguments
;
;       DS:SI - The string to iterate. It must be null-terminated.
;
PrintString:
    cmp si, 0
    je .Return
.Loop:
    lodsb
    cmp al, 0
    je .Return
    mov ah, 0x0e
    int 0x10
    jmp .Loop
.Return:
    ret

;
; Disk Address Packet
;

PrimaryStageDap:
    db 16
    db 0
    dw 1
    dw 0x0000
    dw 0x0800
    dq 64

;
; Messages
;
Message_LoadingPrimaryStageFailed:
    db 'vqbootsector: Loading the primary stage failed'
    db 13, 10, 0

;
; Disk-associated
;
DriveNumber db 0

times 510-($-$$) db 0
dw 0xaa55
