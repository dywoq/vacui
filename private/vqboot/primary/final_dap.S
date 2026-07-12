;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;        This assembly file contains a DAP of the bootloader final stage.
;

%ifndef _FINAL_DAP_S
%define _FINAL_DAP_S

FinalDAP:

        db 16
        db 0
        dw 2
        dw 0x0000
        dw 0x1000
        dq 128

%endif

