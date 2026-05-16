; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; The lowest entry point of installer

section .start
global PreStartup
extern Startup

PreStartup:
    call Startup
