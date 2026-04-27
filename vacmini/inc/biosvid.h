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

VOID
BiosTeletypeOutput(
	IN CHAR character,
	IN CHAR pageNumber,
	IN CHAR attribute
	);

#endif
