// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

__asm(".code16gcc");

void
Hub()
{
    __asm volatile("int $0x10\n" : : "a"(0x0E00 | 'A'));
    while (true)
        __asm volatile("hlt");
}

