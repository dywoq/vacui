/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:
        Compiler-extension macro wrappers
*/

#ifndef _VQCMPEXT_H
#define _VQCMPEXT_H

#if __GNUC__
#define _PACKED        __attribute__((packed))
#define _NORETURN      __attribute__((noreturn))
#define _SECTION(name) __attribute__((section(name)))
#else
#define _PACKED
#define _NORETURN
#define _SECTION(name)
#endif

#endif
