// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <std/types.h>
#include <vga/output.h>

void hub() {
    vga_output_str("Hi!");
    while (true) {
        __asm volatile("hlt\n");
    }
}
