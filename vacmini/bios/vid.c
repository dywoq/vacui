/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	bios/vid.c
 *
 * Module description:
 * 	An implementation of biosvid.h header
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

__asm(".code16gcc");

#include <vqtypes.h>
#include <vqdef.h>

VOID
BiosTeletypeOutput(
	IN BYTE character,
	IN BYTE pageNumber,
	IN BYTE attribute
	)
{
	__asm volatile(
		"int $0x10\n"
		:
		: "a" ((0x0E << 8) | character), "b" ((pageNumber << 8) | attribute)
		: "cc", "memory");
}

