; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Module description:
; 	A boot sector of 'vacui16'. It's loaded at 0x7c00, and it must fit 
; 	into one sector (single sector = 512 bytes).
;	
;	The boot sector loads a kernel, using extended read and its 
;	Disk Address Packet.

bits 16
org 0x7c00

Start:
	cli
	xor ax, ax
	mov es, ax
	mov ds, ax
	mov ss, ax
	mov sp, 0x7c00
	sti

	mov ah, 0x42
	mov si, KernelDap
	mov dl, 0x80
	int 0x13
	jc .diskError

	jmp 0x1000:0x0000

.diskError:
	mov si, DISK_ERROR_FAILED_TO_LOAD_KERNEL
	call Print
	jmp .loop
.loop:
	hlt
	jmp .loop

; Description:
; 	Prints a message into the screen, using BIOS video services 
;	interrupt.
;	
;	During loop, it loads a byte from string and increments it, 
;	printing every character. Stops if al is 0.
; 
; Parameters:
; 	
;	si = A pointer to the string.
Print:
.loop:
	cmp [si], 0
	je .done
	lodsb

	mov ah, 0x0e
	cmp al, 0
	jne .interrupt
	je .done
.interrupt:
	int 0x10
	jmp .loop
.done:
	ret

KernelDap:
	db 16
	db 0
	dw 2
	dw 0x0000
	dw 0x1000
	dq 1

; Error messages
DISK_ERROR_FAILED_TO_LOAD_KERNEL db 'DISK ERROR: Failed to load kernel', 0

times 510-($-$$) db 0
dw 0xaa55
