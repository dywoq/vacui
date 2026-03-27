// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/troot/print.h>
#include <zero/vid/text.h>

[[noreturn]] void troot_entry ()
{
        auto pos = troot_print ("Hi\n", 0, 0);
        pos = troot_print ("S\n", pos.row, pos.col);
        pos = troot_print ("Hello, world!\n", pos.row, pos.col);
        while (true)
                __asm volatile ("hlt\n");
}
