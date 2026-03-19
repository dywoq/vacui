// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>
#include <compiler/ld.h>
#include <hub/panic.h>
#include <hub/print.h>
#include <std/types.h>

void hub() {
    compiler_ld_size_init();

    hub_printnf_dbg("This is the debug build of Zero.\n"
                    "Expect debug messages and not-optimized functions.\n");

    hub_printnf_dbg("Test.\n");

    while (true) {
        __asm volatile("hlt\n");
    }
}
