; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

section .text

; Setups a boot video information, 
; calling bios interuption which changes video mode to 0x13.
;
; Registers (pushed/popped): bx, ax
boot_video_info_setup:
        ; Push used registers to stack
        push ax

        ; Set values
        mov word [boot_video_data], 0x13
        mov word [boot_video_data + 2], 320
        mov word [boot_video_data + 4], 200

        ; Change VGA mode to [boot_video_data]
        xor ah, ah
        mov ax, word [boot_video_data]
        int 0x10

        ; Pop used registers
        pop ax
        ret

section .data
boot_video_data:
    dw 0 ; VGA Mode 
    dw 0 ; Width
    dw 0 ; Height
