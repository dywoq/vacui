section .start
global _start
extern pre

_start:
    push ebx
    call pre
