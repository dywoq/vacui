/* Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	vacpanic.h
 *
 * Module description:
 * 	Kernel panic mechanism
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

#ifndef _VACPANIC_H
#define _VACPANIC_H

#include <vacdef.h>
#include <vactypes.h>

/*
 * Routine description:
 * 	Causes a kernel to panic, printing a panic message 
 * 	into the screen.
 *
 * 	Exits services and cleans up resource.
 *	
 *	Doesn't returns, due to infinite halt.
 *
 * Parameters:
 *
 * 	str	Panic message
 * 	- The function prints '<unknown>' if str is null.
 */
VAC_VOID
Vac_Panic(
	IN OPT const VAC_CHAR *str
	);

#endif
