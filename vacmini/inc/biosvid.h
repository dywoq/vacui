/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	biosvid.h
 *
 * Module description:
 * 	Thin wrappers around BIOS video serivces interrupt
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

#ifndef _BIOSVID_H
#define _BIOSVID_H

#include <vqtypes.h>
#include <vqdef.h>

typedef USHORT BIOS_VIDMODE;

#define BIOS_VID_X80_25 	(BIOS_VIDMODE)0x03
#define BIOS_VID_X320_200	(BIOS_VIDMODE)0x13

VOID
BiosSetVidMode(
	IN BIOS_VIDMODE newMode
	);

VOID
BiosTeletypeOutput(
	IN BYTE character,
	IN BYTE pageNumber,
	IN BYTE attribute
	);

#endif
