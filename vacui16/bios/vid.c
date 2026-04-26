/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	bios/vid.c
 *
 * Module description:
 * 	The source file of biosvid.h header.
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

__asm(".code16gcc");

#include <vactypes.h>
#include <vacdef.h>
#include <biosvid.h>

VAC_VOID
BiosTeletypePut(
	IN VAC_CHAR character
	)
{
	__asm volatile( 			  
			"int $0x10\n" 			 		
			:				
			: "a" ((0x0E << 8) | character)
			: "cc");
}

VAC_VOID
BiosTeletypePrint(
	IN const char* string	
	)
{
	if (!string)
		return;

	for (const char *ptr = string; *ptr != '\0'; ++ptr) {
		char ch = *ptr;
		BiosTeletypePut(ch);
	}
}
