// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <bios/vid.h>
#include <hub/panic.h>
#include <std/types.h>

void hub() {
    hub_panic("HSD");
    while (true) {
        __asm volatile("hlt\n");
    }
}
