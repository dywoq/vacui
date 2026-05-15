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

boot_mm:
    dd 0 ; entries count
    dd 0 ; memory entries

boot_info:
    dd boot_kernel_mode
    dd boot_video
    dd boot_mm

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
    mov ah, 0x0
    mov al, BOOT_VGA_320_200_16_COLORS
    int 0x10
    jmp .return
.mode_640_200_16_colors:
    mov si, VGA_640_200_16_COLORS_MSG
    call print_str
    mov byte [boot_video], BOOT_VGA_640_200_16_COLORS
    mov ah, 0x0
    mov al, BOOT_VGA_640_200_16_COLORS
    int 0x10
    jmp .return
.return:
    ret

; Gets the memory map, using E820 method. 
; In case of success, it writes entries count and a pointer to memory map buffer to boot_mm.
; 
; Halts and prints error message if it fails to get memory map. 
get_mm_map:
    xor ebx, ebx
    xor bp, bp
    mov di, boot_mm_map_buffer
.loop:
    mov eax, 0xE820
    mov edx, 0x534D4150
    mov ecx, 20
    int 0x15
    jc .error
    cmp eax, 0x534D4150
    jne .error

    add di, 20
    inc bp

    cmp bp, 40
    je .finish

    test ebx, ebx
    jnz .loop
.finish:
    movzx eax, bp
    mov dword [boot_mm], eax
    mov dword [boot_mm + 4], boot_mm_map_buffer
    ret
.error:
    mov si, FAILED_TO_GET_MEMORY_MAP
    call print_str
.halt:
    hlt
    jmp .halt

; Memory map buffer
boot_mm_map_buffer:
    resb 800 ; 20 bytes * 40 entries

; Messages
SELECT_KERNEL_MODE_MSG db 'Select kernel mode [0 - Normal, 1 - Recovery]', 13, 10, 0
KERNEL_MODE_NORMAL db '* Normal mode is selected', 13, 10, 0
KERNEL_MODE_RECOVERY db '* Recovery mode is selected', 13, 10, 0

SELECT_VGA_MODE db 'Select VGA mode [0 - 320x200 16 colors, 1 - 640x200 16 colors]', 13, 10, 0
VGA_320_200_16_COLORS_MSG db '* 320x200 16 colors mode is selected', 13, 10, 0
VGA_640_200_16_COLORS_MSG db '* 640x200 16 colors mode is selected', 13, 10, 0

FAILED_TO_GET_MEMORY_MAP db 'ERROR: Failed to get memory map', 13, 10, 0

%endif
