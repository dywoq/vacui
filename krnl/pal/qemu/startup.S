// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// CRT0 function for QEMU emulator. Jumps to its C-side entry function.

.global startup
.extern qemu_entry

.section .bss
.balign 16 
_stack_start:
    .space 4096 
_stack_top:

.section .start 
startup:
    la sp, _stack_top
    call qemu_entry
    