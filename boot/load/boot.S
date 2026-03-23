; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

; A boot video information about video mode.
struc BootVideoInfo
        .mode resw 1
        .width resw 1
        .height resw 1
endstruc

; A boot information.
struc BootInfo
        .video resb BootVideoInfo_size
endstruc

