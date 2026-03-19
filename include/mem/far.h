// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _MEM_FAR_H
#define _MEM_FAR_H

#include <std/types.h>

#define mem_far_readb(b, segment, offset)                                      \
    do {                                                                       \
        ubyte_t __tmp;                                                         \
        uword_t __ofs = (offset);                                              \
        uword_t __seg = (segment);                                             \
        __asm volatile("movw %1, %%ax\n\t"                                     \
                       "movw %%ax, %%ds\n\t"                                   \
                       "movw %2, %%bx\n\t"                                     \
                       "movb %%ds:(%%bx), %%al\n\t"                            \
                       "movb %%al, %0"                                         \
                       : "=q"(__tmp)                                           \
                       : "r"(__seg), "r"(__ofs)                                \
                       : "ax", "bx", "memory");                                \
        (b) = __tmp;                                                           \
    } while (0)

#define mem_far_writeb(val, segment, offset)                                   \
    do {                                                                       \
        ubyte_t __tmp = (val);                                            \
        uword_t __ofs = (offset);                                              \
        uword_t __seg = (segment);                                             \
        __asm volatile("movw %1, %%ax\n\t"                                     \
                       "movw %%ax, %%es\n\t"                                   \
                       "movw %2, %%di\n\t"                                     \
                       "movb %0, %%al\n\t"                                     \
                       "movb %%al, %%es:(%%di)"                                \
                       :                                                       \
                       : "q"(__tmp), "r"(__seg), "r"(__ofs)                    \
                       : "ax", "di", "memory");                                \
    } while (0)

#endif
