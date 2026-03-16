// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <std/types.h>

void hub() {
    while (true) {
        __asm volatile("hlt\n");
    }
}
