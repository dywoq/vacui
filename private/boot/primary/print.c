//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      This source file is an implementation of the print.h header
//

__asm(".code16gcc");

#include "print.h"

#include <hlbvid.h>

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
    HlbVideoTeletypeOutput(Character);
}
