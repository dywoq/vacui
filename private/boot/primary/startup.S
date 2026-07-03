;
; Copyright 2026 dywoq - Apache License 2.0
; https://github.com/dywoq/vacui
;
; Description:
;
;	Boot primary stage startup code
;

bits 	16
global 	__start
extern  _BootPrimary

__start:
	
	cli
	xor ax, ax
	mov es, ax
	mov ds, ax
	mov ss, ax
	mov sp, 0x7bff
	sti

	call _BootPrimary
