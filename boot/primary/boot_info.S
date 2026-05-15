; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

%ifndef _BOOT_INFO_S
%define _BOOT_INFO_S

boot_kernel_mode:
    db 0 ; kernel_mode

%define BOOT_VGA_320_200_16_COLORS 0x0D
%define BOOT_VGA_640_200_16_COLORS 0x0E 
boot_video:
    db 0 ; vga mode 
    
boot_info:
    dd boot_kernel_mode
    dd boot_video

; Blocks CPU execution and asks the user for kernel mode.
; After getting the input it puts the info into boot_kernel_mode.
get_kernel_mode:
    ; 0 - Normal mode
    ; 1 - Recovery mode
    mov si, SELECT_KERNEL_MODE_MSG
    call print_str
.loop:
    mov ah, 0x00
    int 0x16
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

; Blocks CPU execution and asks the user for VGA mode.
; Works similar as get_kernel_mode 
get_vga_mode:
    ; 0 - BOOT_VGA_320_200_16_COLORS
    ; 1 - BOOT_VGA_640_200_16_COLORS
    mov si, SELECT_VGA_MODE
    call print_str
.loop:
    mov ah, 0x00
    int 0x16
    cmp al, '0'
    je .mode_320_200_16_colors
    cmp al, '1'
    je .mode_640_200_16_colors
    jmp .loop
.mode_320_200_16_colors:
    mov si, VGA_320_200_16_COLORS_MSG
    call print_str
    mov byte [boot_video], BOOT_VGA_320_200_16_COLORS
    jmp .return
.mode_640_200_16_colors:
    mov si, VGA_640_200_16_COLORS_MSG
    call print_str
    mov byte [boot_video], BOOT_VGA_640_200_16_COLORS
    jmp .return
.return:
    ret

; Messages
SELECT_KERNEL_MODE_MSG db 'Select kernel mode [0 - Normal, 1 - Recovery]', 13, 10, 0
KERNEL_MODE_NORMAL db '* Normal mode is selected', 13, 10, 0
KERNEL_MODE_RECOVERY db '* Recovery mode is selected', 13, 10, 0

SELECT_VGA_MODE db 'Select VGA mode [0 - 320x200 16 colors, 1 - 640x200 16 colors]', 13, 10, 0
VGA_320_200_16_COLORS_MSG db '* 320x200 16 colors mode is selected', 13, 10, 0
VGA_640_200_16_COLORS_MSG db '* 640x200 16 colors mode is selected', 13, 10, 0

%endif
