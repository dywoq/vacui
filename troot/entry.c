// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/vid/text.h>

[[noreturn]] void troot_entry ()
{
        vid_text_put ("Entered TerminalRoot (troot) mode", 15, 0, 0, 0);
        while (true)
                __asm volatile ("hlt\n");
}
