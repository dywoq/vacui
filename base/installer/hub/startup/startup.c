/*
 * Copyright 2026 dywoq - Apache License 2.0
 * https://github.com/dywoq/vacui
 *
 * The entry of Vacui installer
 */

[[noreturn]]
void
startup()
{
    while (1)
        __asm volatile("hlt\n");
}
