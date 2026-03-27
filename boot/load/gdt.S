; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

%ifndef _BOOT_LOAD_GDT_S
%define _BOOT_LOAD_GDT_S

; Each GDT entry weights 8 bytes
gdt_start:
        ; Null descriptor
        dq 0

        ; Kernel code segment descriptor
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 10011010b
        db 11001111b
        db 0x00

        ; Kernel data segment descriptor
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 10010010b
        db 11001111b
        db 0x00
gdt_end:

gdt_ptr:
        dw gdt_end - gdt_start - 1
        dd gdt_start

%endif
