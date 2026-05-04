// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Entry function of QEMU platform.
//
// The source file setups the necessary information to provide for the main
// kernel. and jumps to the main kernel.

void qemu_entry()
{
    extern void hub();
    hub();
    while (1)
        ;
}
