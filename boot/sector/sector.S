; Copyright 2026 dywoq - Apache License 2.0;
; A part of https://github.com/dywoq/vacui

Dap STRUCT 
        dapSize db 16 
        reserved db 0 
        sectorCount dw 0 
        destOffset dw 0 
        destSegment dw 0 
        lba dq 0 
Dap ENDS 

BOOT SEGMENT 
        org 0x7c00 

        ; Prototype functions
        PrintStr PROTO C :WORD

        Start: 
                cli 
                xor ax, ax 
                mov ds, ax 
                mov es, ax 
                mov ss, ax 
                mov sp, 0x7c00 
                sti 

                ; Read load stage from the first HDD(0x80).
                mov ah, 0x42 
                mov dl, 0x80 
                mov si, loadDap 
                int 0x13 
                .if CARRY? 
                        invoke PrintStr, offset errorLoadStageGetFailure 
                        jmp @@loop
                .endif
                
                push loadDap.destSegment
                push loadDap.destOffset
                retf

        @@loop: 
                hlt 
                jmp @@loop

        ; Prints a string into the screen, using BIOS interrupt.
        PrintStr PROC C string:WORD
                mov si, string
                .while (byte ptr [si] != 0)
                        lodsb
                        mov ah, 0x0E
                        .if (al != 0)
                                int 0x10
                        .endif 
                .endw
                ret
        PrintStr ENDP
        
        loadDap Dap <16, 0, 2, 0x0, 0x0800, 1>

        ; Error messages 
        errorLoadStageGetFailure db "ERROR: Failed to load 'Load stage' from the disk", 0xD, 0xA, 0
        
        org 0x7c00 + 510 
        dw 0xaa55 
BOOT ENDS 

end Start
