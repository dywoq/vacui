// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#include <vacui/kernel/hub/debug.hxx>

extern "C" void
Hub()
{
    using namespace vacui::kernel::hub;
    debug::LogStr("Starting kernel loop\r\n");
    for (;;)
        __asm volatile("wfi\n");
}

