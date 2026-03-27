; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/zero

%ifndef _BOOT_LOAD_MEM_S
%define _BOOT_LOAD_MEM_S

; Gets a memory map using E820 method, iterating
; over memory map entries and storing in boot_mem_map.
;
; Calls 'stc' if it fails to get the memory map.
boot_mem_setup:
        xor ebx, ebx
        mov di, boot_mem_buffer
        mov edx, 0x534D4150
.loop:
        ; Request 20 bytes (since the hardware uses ACPI 1.0 before 2000s).
        mov eax, 0xE820
        mov ecx, 20
        int 0x15
        jc .error
        cmp eax, 0x534D4150
        jne .error
        
        ; Move pointer by 20 bytes and 
        add di, 20 
        inc word [boot_mem_map]

        ; Check if boot_mem_map entries count is over 40.
        cmp word [boot_mem_map], 40
        je .finish
        
        ; If ebx equals to zero, we return.
        test ebx, ebx
        jnz .loop
                
.error:
        stc
        ret
.finish:
        mov dword [boot_mem_map + 4], boot_mem_buffer
        ret

section .data
boot_mem_map:
        dd 0 ; Entries count
        dd 0 ; Buffer with memory entries

section .bss
boot_mem_buffer: 
        resb 800 ; 20 bytes each entry * 40 entries

%endif
