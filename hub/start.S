; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

section .start
global _start
extern hub

_start:
    push ebx
    call hub
