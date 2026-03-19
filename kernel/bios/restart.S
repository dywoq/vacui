// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

.code16
.section .text
.global bios_sys_cold_restart, bios_restart_warm

bios_restart_cold:
    movw $0x40, %ax
    movw %ax, %ds
    movw $0x0000, 0x72
    ljmp $0xFFFF, $0x0000

bios_restart_warm:
    movw $0x40, %ax
    movw %ax, %ds
    movw $0x1234, 0x72
    ljmp $0xFFFF, $0x0000
