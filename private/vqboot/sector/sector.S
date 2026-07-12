;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;        Vacui bootloader sector
;

bits 16
org 0x7C00

SectorStartup:

        cli
        xor ax, ax
        mov es, ax
        mov ds, ax
        mov ss, ax
        mov sp, 0x7C00
        sti

        ;
        ; Load the primary boot stage into the memory.
        ;
        mov ah, 0x42
        mov si, PrimaryDAP
        mov dl, 0x80
        int 0x13
        jc .diskError

        ;
        ; Perform a far jump
        ;
        jmp 0x0800:0x0

        .diskError:
        mov si, ERR_FailedToLoadPrimaryBootStage
        call PrintStr
        jmp .halt

        .halt:
        hlt

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

PrimaryDAP:
        
        db 16           ; Packet sie
        db 0            ; Reserved
        dw 2            ; How much sectors do we read
        dw 0x0000       ; Offset
        dw 0x0800       ; Segment
        dq 64           ; LBA start

;
; A data block with null-terminated erorr messages
;
ERR_FailedToLoadPrimaryBootStage:
        db 'vacui: Failed to load the bootloader primary stage into memory.'
        db 13, 10, 0

times 510-($-$$) db 0
dw 0xAA55

