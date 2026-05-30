; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;   Global Descriptor Table struct definition

%ifndef _GDT_S
%define _GDT_S

; Description:
;
;   Global Definition Table instance.
;
;   It's temporary GDT instance, and only used to survive transition to
;   protected mode to real mode.
gdt_start:
    dq 0                  ; Null desc
    dq 0x00CF9A000000FFFF ; Kernel Code Segment
    dq 0x00CF92000000FFFF ; Kernel Data Segment
gdt_end:

gdt_ptr:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    
%endif
