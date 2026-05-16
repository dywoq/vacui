; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui

%ifndef _DAP_S
%define _DAP_S

bits 16

InstallerDap:
    db 16
    db 0
    dw 1
    dw 0x0
    dw 0x1000
    dq 2

%endif
