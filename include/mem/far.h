// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _MEM_FAR_H
#define _MEM_FAR_H

#define mem_far_readb(b, segment, offset)                                      \
    do {                                                                       \
        unsigned char __tmp;                                                   \
        unsigned short __ofs = (offset);                                       \
        unsigned short __seg = (segment);                                      \
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
        unsigned char __tmp = (val);                                           \
        unsigned short __ofs = (offset);                                       \
        unsigned short __seg = (segment);                                      \
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
