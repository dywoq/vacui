; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;   Contains the code of Boot Sector in BAL i386

bits 16
org 0x8000

_start:

    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    ;
    ; Enable A20
    ;
    in al, 0x92
    or al, 2
    out 0x92, al

    ;
    ; Load final bootloader stage
    ;
    mov ah, 0x42
    mov si, final_dap
    int 0x13
    jc .disk_error

    ;
    ; Real mode -> Protected mode transition
    ;
    cli
    lgdt [gdt_ptr]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp 0x08:pm_start
    hlt

.disk_error:
    mov si, MSG_FAILED_TO_LOAD_FINAL_STAGE
    call print_str
    jmp .halt

.halt:
    hlt
    jmp .halt


bits 32
%include "gdt.S"
; Description:
;
;   Protected mode start
pm_start:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    jmp 0x10000

bits 16
%include "print.S"

; Description:
;
;   Final Bootloader stage Disk Address Packet
final_dap:
    db 16
    db 0
    dw 1
    dw 0x0
    dw 0x1000
    dq 2

; Messages
MSG_FAILED_TO_LOAD_FINAL_STAGE:
    db '[Vacui BAL i386] Failed to load final bootloader stage'
    db 13
    db 10
    db 0


times 512-($-$$) db 0
