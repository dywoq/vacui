;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Module Description
;
;       VQBoot primary stage startup
;

bits 16
global PrimaryStartup
extern PrimaryEntry

section .entry
PrimaryStartup:
    cli
    xor ax, ax
    mov es, ax
    mov ds, ax
    mov ss, ax
    mov sp, 0x7bff
    sti

    call PrimaryEntry
