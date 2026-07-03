;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;	Boot sector assembly code
;

bits 	16
org 	0x7c00

SectorStartup:
	
	cli
	xor ax, ax
	mov es, ax
	mov ds, ax
	mov ss, ax
	mov sp, 0x7c00
	sti
	
	;
	; Try to read the boot primary steage DAP 
	;
	mov ah, 0x42
	mov si, BootPrimaryDap
	int 0x13
	jc .diskError

	jmp 0x0800:0x0000

.diskError:
	;
	; Print disk error
	;
	mov si, ERROR_FailedToLoadBootPrimary
	call PrintAscii
	jmp .hlt
.hlt:
	hlt
	jmp .hlt 

BootPrimaryDap:

	db 16		; DAP size
	db 0		; Rseserved
	dw 2		; Sectors count
	dw 0x0000	; Offset
	dw 0x0800	; Segment
	dq 1		; LBA start
;
; Description:
;
;	Using BIOS teletype output interrupt, PrintAscii prints the characters
;	gradually during a string iteration.
;
; Parameters:
;
;	ES:SI - The null-terminated string to print.
;
; Returns:
;
;	- Returns the control if these conditions are true:
;		if [SI] == 0 
;		if AL == 0 (if the iteration is already started)
;
PrintAscii:
.loop:
	cmp [si], 0
	je .return
	lodsb
	cmp al, 0
	je .return
	mov ah, 0x0e
	int 0x10
	jmp .loop
.return:
	ret

ERROR_FailedToLoadBootPrimary:

	db 'vacui: Failed to load Boot Primary stage'
	db 13, 10, 0

times 510-($-$$) db 0
dw 0xaa55

