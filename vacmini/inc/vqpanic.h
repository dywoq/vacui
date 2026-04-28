/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	vqpanic.h
 *
 * Module description:
 * 	Definition of kernel panic function mechanism, 
 * 	that are used for fatal errors.
 *
 * 	During panic, kernel halts and doesn't return.
 *
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */

#ifndef _VQPANIC_H
#define _VQPANIC_H

#include <vqdef.h>
#include <vqtypes.h>

_Noreturn
VOID
Panic(
	C_STR string);

#endif
