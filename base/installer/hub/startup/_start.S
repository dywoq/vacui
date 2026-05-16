; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; The lowest entry point of installer

section .start
global _start
extern startup

_start:
    call startup
