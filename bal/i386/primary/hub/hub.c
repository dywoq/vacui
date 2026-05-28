// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui

__asm(".code16gcc");

#include <balinfo.h>
#include <hub.h>

static struct bal_info *boot_info_ = {};

[[noreturn]] void hub()
{
    boot_info_->metadata->name = "Vacui BAL i386";
    boot_info_->metadata->license = "Apache License 2.0";
    while (1)
        __asm volatile("hlt\n");
}
