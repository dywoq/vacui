/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	hub/print.c
 *
 * Module description:
 * 	An implementation of vqprint.h header
 * 	 
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

__asm(".code16gcc");

#include <vqtypes.h>
#include <vqdef.h>
#include <biosvid.h>

VOID
Put(
	IN BYTE character)
{
	BiosTeletypeOutput(character, 0, 0x07);	
}

VOID
Print(
	IN C_STR string)
{
	for (C_STR ptr = string; *ptr != '\0'; ++ptr) 
	{
		if (*ptr == '\n') 
		{
			Put('\n');
			Put('\r');
			continue;
		}
		Put(*ptr);
	}
}
