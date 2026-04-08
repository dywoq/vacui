// Copyright 2026 BellusTM - Apache License 2.0
// A part of https://github.com/bellustm/vacui

#include <vacui/kernel/base/print.hxx>

extern "C" void
Hub()
{
    using namespace vacui::kernel::base;
    PrintStr("Hi!");
    for (;;)
        __asm volatile("wfi\n");
}

