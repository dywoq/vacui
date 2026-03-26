; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

section .text

; Setups a boot video information, 
; calling bios interuption which changes video mode to 0x13.
;
; The VGA mode depends on boot mode.
; - If TerminalRoot => VGA Mode 0x03
; - If GUI => VGA Mode 0x13
;
; Registers (pushed/popped): ax
boot_video_info_setup:
        ; Push used registers to stack
        push ax

        ; If boot mode is TerminalRoot
        cmp byte [boot_mode_info], 0
        je .turn_vga_0x03

        ; If boot mode is GUI
        cmp byte [boot_mode_info], 1
        je .turn_vga_0x13

.turn_vga_0x03:
        mov word [boot_video_data], 0x03
        mov word [boot_video_data + 2], 80
        mov word [boot_video_data + 4], 25
        mov ax, 0x03
        int 0x10
        jmp .finally
.turn_vga_0x13:
        mov word [boot_video_data], 0x13
        mov word [boot_video_data + 2], 320
        mov word [boot_video_data + 4], 200
        mov ax, 0x13
        int 0x10
        jmp .finally
.finally:
        pop ax
        ret

section .data
boot_video_data:
    dw 0 ; VGA Mode 
    dw 0 ; Width
    dw 0 ; Height
