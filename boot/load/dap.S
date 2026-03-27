; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

%ifndef _BOOT_LOAD_DAP_S
%define _BOOT_LOAD_DAP_S

kernel_dap:
        db 16
        db 0
        dw 2
        dw 0x0000
        dw 0x1000
        dq 2

%endif
