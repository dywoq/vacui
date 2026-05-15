; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

section .start
global _start
extern pre

_start:
    push ebx
    call pre
