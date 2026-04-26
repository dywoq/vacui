/*
 * Copyright 2026 dywoq - Apache License 2.0
 * A part of https://github.com/dywoq/vacui
 *
 * Module name:
 * 	vactypes.h
 *
 * Module description:
 * 	Shortcut types, integral types
 *
 * History:
 * 	Apr-26 9:44 AM 2026
 * 	- Creation date
 *
 * 	Apr-26 10:29 AM 2026
 * 	- Add VAC_VOID type alias.
 * 	- Make VAC_PVOID use VAC_VOID*, instead of just void *. 
 * Authors:
 * 	dywoq dywoq.contact@gmail.com
 */
#ifndef _VACTYPES_H
#define _VACTYPES_H

typedef char 			VAC_CHAR;
typedef short			VAC_SHORT;
typedef int			VAC_INT;
typedef long long 		VAC_LONG;

typedef unsigned char 		VAC_UCHAR;
typedef unsigned short 		VAC_USHORT;
typedef unsigned int 		VAC_UINT;
typedef unsigned long long 	VAC_ULONG;

typedef void			VAC_VOID;
typedef VAC_VOID *		VAC_PVOID;

#endif
