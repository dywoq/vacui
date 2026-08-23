;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Routine Description
;
;       The VQBoot sector stage. It is responsible for loading and executing 
;       the kernel.
;

org 0x7c00
bits 16

SectorEntry:

        cli
        xor ax, ax
        mov es, ax
        mov ds, ax
        mov ss, ax
        mov sp, 0x7bff
        sti

.LoadKernel: 
        mov si, Message_LoadingKernel
        call PrintString
        
        mov ah, 0x42
        mov si, KernelDAP
        int 0x13
        jc .DiskFailure
        jnc .ExecuteKernel

.ExecuteKernel:
        mov si, Message_ExecutingKernel
        call PrintString
        jmp 0x0800:0x0000
        jmp .Loop

.DiskFailure:
        mov si, Message_FailedToLoadKernel
        call PrintString
        jmp .Loop

.Loop:
        jmp .Loop
        hlt

;
; Messages
;

Message_LoadingKernel 
        db '[VQBoot] Loading the kernel'
        db 10, 13, 0
Message_FailedToLoadKernel
        db '[VQBoot] Failed to load the kernel.'
        db 10, 13, 0
Message_ExecutingKernel
        db '[VQBoot] Executing the kernel'
        db 10, 13, 0

;
; Data
;

KernelDAP:
        db 16
        db 0
        dw 2
        dw 0x0000
        dw 0x0800
        dq 64

;
; Modules
;

%include "print.S"

times 510-($-$$) db 0
dw 0xaa55

