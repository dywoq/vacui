/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	vqprint.h
 *
 * Module description:
 * 	Print functions.
 * 	They work only if the video mode is text one.
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */
#ifndef _VQPRINT_H
#define _VQPRINT_H

#include <vqtypes.h>
#include <vqdef.h>

VOID
Put(
	IN BYTE character);

VOID
Print(
	IN C_STR string);

#endif
