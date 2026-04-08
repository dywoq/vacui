# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

# Allocate stack for 4096 bytes
.section .bss
.align 16
__stack_bottom:
        .space 4096
__stack_top:

.section .start, "ax"
.global _start
_start:
        la sp, __stack_top
        call Hub
