; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

section .data
__mode_S_ENABLE_TERMINAL_MODE_ROOT db "Enable TerminalRoot mode? (y/n)"

boot_mode_info:
        db 0 ; 0 = TerminalRoot, 1 = GUI

section .text
block_and_ask_for_mode:
        mov si, __mode_S_ENABLE_TERMINAL_MODE_ROOT
; Print a message into the screen
.print_loop:
        lodsb
        test al, al
        jz .pause
        mov ah, 0x0E
        mov bh, 0
        int 0x10
        jmp .print_loop
; Pauses and waits for the key (int 0x16 blocks the execution).
; If y => TerminalRoot mode (troot)
; If n => Graphical user interface mode (GUI)
.pause:
        xor ah, ah
        int 0x16
        cmp al, 'y'
        je .turn_troot
        cmp al, 'n'
        je .turn_gui
        jne .pause
.turn_troot:
        mov [boot_mode_info], 0
        ret
.turn_gui:
        mov [boot_mode_info], 1
        ret
