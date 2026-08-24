//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      Kernel engine initialization
//

__asm(".code16gcc");

void
KeInitialize()
{
    while (1)
    {
        __asm volatile("hlt\n");
    }
}
