// Copyright 2026 BellusTM - Apache License 2.0
// A part of https://github.com/bellustm/vacui

#include <vacui/kernel/base/print.hxx>
#include <vacui/kernel/hub/panic.hxx>

extern "C" void
Hub()
{
    using namespace vacui::kernel::base;
    using namespace vacui::kernel::hub;
    Panic("Test");
    PrintStr("Hi!");
    for (;;)
        __asm volatile("wfi\n");
}

