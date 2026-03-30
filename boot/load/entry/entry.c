// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#include <zero/types.h>

void entry() {
        while (true) {
                __asm volatile ("hlt\n");
        }
}
