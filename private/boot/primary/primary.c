/*
    Copyright 2026 dywoq - Apache License 2.0
    https://github.com/dywoq/vacui

    Description:

        Boot Primary stage C-side main function
*/

void
BootPrimary()
{
    while (1)
    {
        asm("hlt\n");
    }
}
