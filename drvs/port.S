; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

section .text
global drvs_port_outb 
global drvs_port_inb

; Signature:
; void __cdecl drvs_port_outb (ubyte_t value, uword_t port);
drvs_port_outb:
        push ebp
        mov ebp, esp

        mov al, [ebp+8]      ; Value
        mov dx, [ebp+12]     ; Port
        out dx, al           ; Write to the port

        mov esp, ebp
        pop ebp 
        ret

; Signature:
; ubyte_t __cdecl drvs_port_inb (uword_t port);
drvs_port_inb:
        push ebp
        mov ebp, esp

        mov dx, [ebp + 8] ; Port
        mov al, 0 ; Value
        in al, dx ; Read it

        mov esp, ebp
        pop ebp
        ret
