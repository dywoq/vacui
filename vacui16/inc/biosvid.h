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

VAC_VOID
BiosTeletypePut(
	IN VAC_CHAR character
	);

VAC_VOID
BiosTeletypePrint(
	IN const VAC_CHAR* string	
	);

#endif
