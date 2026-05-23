// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

[[noreturn]] void hub()
{
    while (1)
        __asm volatile("hlt\n");
}
