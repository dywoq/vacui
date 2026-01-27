; Copyright (c) 2026 dywoq
;
; This code is released under the MIT License.
; https://opensource.org/licenses/MIT
;
; Repository:
; https://github.com/dywoq/vacui

%ifndef _VACUI_KERNEL_
%define _VACUI_KERNEL_

; Represents the entry point of whole OS, which bootloader jumps to.
kernel:
.hang:
    hlt
    jmp .hang

%endif