/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	biosvid.h
 *
 * Module description:
 * 	Wrappers around BIOS video services interrupts.
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */
#ifndef _BIOSVID_H
#define _BIOSVID_H

#include <vactypes.h>
#include <vacdef.h>

/*
 * Routine description:
 * 	A thin wrapper around BIOS interrupt teletype output.
 * 	The form:
 * 		bh = 0
 * 		eax = (0xE << 8) | character
 *		int = 0x10
 *
 * Parameters:
 * 	character	Character to output
 *
 */
VAC_VOID
BiosTeletypePut(
	IN VAC_CHAR character
	);

/*
 * Routine description:
 * 	Iterates over string and calls BiosTeletypePut,
 * 	providing the current iterated character. 
 * 	
 * 	The function doesn't do anything extra.
 *
 * Parameters:
 * 	string		String to iterate and print
 */
VAC_VOID
BiosTeletypePrint(
	IN const VAC_CHAR* string	
	);

#endif
