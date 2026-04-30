; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Description:
; 
; Startup function of kernel.
; The segments and stack segment/pointer are already set by boot primary stage,
; therefore we need to call entry function from C-side.

section .start
global startup
extern entry

startup:
    call entry
