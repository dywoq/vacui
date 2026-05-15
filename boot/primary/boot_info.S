; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

%ifndef _BOOT_INFO_S
%define _BOOT_INFO_S

boot_kernel_mode:
    db 0 ; kernel_mode
boot_info:
    dd boot_video_mode

; Blocks CPU execution and asks the user for kernel mode.
; After getting the input it puts the info into boot_video_mode.
get_kernel_mode:
    ; 0 - Normal mode
    ; 1 - Recovery mode
    mov si, SELECT_KERNEL_MODE_MSG
    call print_str
.loop:
    mov ah, 0x01
    int 0x16
    jnz .check
.check:
    cmp al, '0'
    je .normal_mode
    cmp al, '1'
    je .recovery_mode
    jmp .loop
.normal_mode:
    mov si, KERNEL_MODE_NORMAL
    call print_str
    mov byte [boot_kernel_mode], 0
    jmp .return
.recovery_mode:
    mov si, KERNEL_MODE_RECOVERY
    call print_str
    mov byte [boot_kernel_mode], 1
    jmp .return
.return:
    ret

; Messages
SELECT_KERNEL_MODE_MSG db 'Select kernel mode [0 - Normal, 1 - Recovery]', 13, 10, 0
KERNEL_MODE_NORMAL db '* Normal mode is selected', 13, 10, 0
KERNEL_MODE_RECOVERY db '* Recovery mode is selected', 13, 10, 0

%endif
