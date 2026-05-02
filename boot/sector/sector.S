; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
; 
; A boot sector.
;
; Since the hardware starts the boot sector, and the boot sector 
; must fit into 512 bytes, we load the primary boot stage.

db 'VQ'

bits 16
org 0x7c00

startup:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    xor ah, ah
    mov ax, 0x03
    int 0x10

    mov si, START_MSG
    call print

    mov si, LOADING_PRIMARY_BOOT_STAGE
    call print

    mov ah, 0x42
    mov si, primary_boot_dap
    int 0x13
    jc .disk_error

    jmp 0x0800:0x0
    
.disk_error:
    mov si, ERROR_OCCURED_MSG
    call print
    mov si, DISK_ERROR_FAILED_TO_LOAD_PRIMARY_BOOT_STAGE
    call print
    mov si, REBOOT_SHUTDOWN_PC_MSG
    call print
    jmp .loop
.loop:
    hlt
    jmp .loop

print:
.loop:
    cmp [si], 0
    je .return
    lodsb
    mov ah, 0x0e
    cmp al, 0
    jne .interrupt
    je .return
.interrupt:
    int 0x10
    jmp .loop
.return:
    ret

primary_boot_dap:
    db 16
    db 0
    dw 3
    dw 0x0
    dw 0x0800
    dq 1

; Info messages
START_MSG db '| vqboot_sector is loaded', 10, 13, 0
LOADING_PRIMARY_BOOT_STAGE db '| Loading Primary Boot stage...', 10, 13, 0
ERROR_OCCURED_MSG db '| ERROR OCCURED:', 10, 13, 0
REBOOT_SHUTDOWN_PC_MSG db '| You can safely shutdown/reboot your PC.', 10, 13, 0

; Errors
DISK_ERROR_FAILED_TO_LOAD_PRIMARY_BOOT_STAGE db '   Failed to load Primary Boot stage', 10, 13, 0

times 510-($-$$) db 0
dw 0xaa55
