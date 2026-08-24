//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      Printing functionality
//

__asm(".code16gcc");

#include "print.h"

void
PrimaryPrintMsg(const char *MessagePtr)
{
    if (!MessagePtr)
    {
        return;
    }

    for (const char *Ptr = MessagePtr; *Ptr != '\0'; ++Ptr)
    {
        PrimaryPrintChar(*Ptr);
    }
}

void
PrimaryPrintChar(char Character)
{
    __asm volatile("int $0x10\n" : : "a"((0x0e << 8) | Character));
}
