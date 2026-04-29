/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	biosdisk.h
 *
 * Module description:
 * 	Thin wrappers around BIOS disk services interrupts
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

#ifndef _BIOSDISK_H
#define _BIOSDISK_H

#include <vqtypes.h>

typedef struct [[gnu::packed]] _BIOS_DAP {
	UBYTE size;
	UBYTE reserved;
	USHORT sectionsCount;
	USHORT offset;
	USHORT segment;
	ULONG start;
} BIOS_DAP, *PBIOS_DAP;

typedef struct [[gnu::packed]] _BIOS_EXTENDED_RESULT {
	UBYTE errorCode;
} BIOS_EXTENDED_RESULT, *PBIOS_EXTENDED_RESULT;

BIOS_EXTENDED_RESULT
BiosExtendedRead(
	UBYTE driveNumber,
	PBIOS_DAP dap
	);

#endif
