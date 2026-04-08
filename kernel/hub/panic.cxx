// Copyright 2026 BellusTM - Apache License 2.0
// A part of https://github.com/bellustm/vacui

#include <vacui/kernel/base/print.hxx>

namespace vacui::kernel::hub
{
    [[noreturn]]
    void
    Panic(const char *msg) noexcept
    {
        base::PrintStr("Kernel panic:\r\n");
        base::PrintStr("* REASON: ");
        base::PrintStr(msg);
        base::PrintStr("\r\n");
        base::PrintStr("* Cannot proceed due to panic.");
        while (true)
            __asm volatile("wfi\n");
    }
} // namespace vacui::kernel::hub

