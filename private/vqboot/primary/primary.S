;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;       This assembly file contains a startup code of 
;       the bootloader primary stage.
;

bits 16
org 0x8000

PrimaryStartup:

        cli
        xor ax, ax
        mov es, ax
        mov ds, ax
        mov ss, ax
        mov sp, 0x7bff
        sti

        ;
        ; Load the bootloader final stage into the memory.
        ;
        mov ah, 0x42
        mov si, FinalDAP
        int 0x13
        jc .diskError

        ;
        ; Enable the paging bit in CR3, load the pointer to GDT Table and 
        ; perform a far jump to the protected mode entry
        ;
        cli
        lgdt [GdtTablePtr]
        mov eax, cr0
        or eax, 0x1
        mov cr0, eax
        jmp 0x08:ProtectedModeEntry

        ;
        ; Print disk error
        ;
        .diskError:
        mov si, ERR_FailedToLoadFinalStage
        call PrintStr

        ; 
        ; Halts and makes the program go into infinity loop
        ;
        .halt:
        hlt
        jmp .halt

;
; Assembly file includes
;
bits 16
%include "print.S"
%include "final_dap.S"

bits 16
;
; Error messages, used within primary.S
;
ERR_FailedToLoadFinalStage:
        db 'vacui: Failed ot load bootloader final stage into the memory'
        db 13, 10, 0

bits 32
%include "gdt.S"

;
; Setups segment registers and performs a far jump,
; executing the bootloader final stage instructions.
;
ProtectedModeEntry:
        
        mov ax, 0x10
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        jmp 0x10000

