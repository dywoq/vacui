;
; Copyright 2026 dywoq - Apache License 2.0
; A part of https://github.com/dywoq/vacui
;
; Module name:
; 	entry/_start.S
;
; Module description:
;	A CRT0 code of kernel 	
;
; Authors:
;	dywoq dywoq.contact@gmail.com
;

bits 16 
section .start
extern Entry

_start:
	cli
	xor ax, ax
	mov es, ax
	mov ds, ax
	mov ss, ax
	mov sp, 0x7bff
	mov esp, 0x7bff
	sti

	call Entry
