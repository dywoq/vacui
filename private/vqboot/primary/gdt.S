;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;       This assembly contains a temporary Global Descriptor Table data
;       and its pointer. It is used to survive protected mode transition only.
;

%ifndef _GDT_S
%define _GDT_S

GdtTable:
        ; Null entry
        dq 0
        ; Kernel code entry
        dq 0xCF9A000000FFFF
        ; Kernel data entry
        dq 0xCF92000000FFFF 
GdtTableEnd:

GdtTablePtr:
        dw (GdtTableEnd - GdtTableEnd) -1
        dd GdtTable

%endif

