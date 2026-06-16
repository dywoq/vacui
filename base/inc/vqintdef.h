/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    This header contains architecture-dependent type aliases
    over integral types.

    WARNING: The Vacui private header.
*/

#ifndef _VQINTDEF_H
#define _VQINTDEF_H

/* For x86-64 */
#if _X86_64_
typedef signed char BYTE;
typedef signed short SHORT;
typedef signed int INT;
typedef signed long long LONG;

typedef unsigned char UBYTE;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long long ULONG;
#endif

#endif
