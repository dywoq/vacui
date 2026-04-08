// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#include <vacui/types.hxx>

namespace vacui::kernel::hub
{
    static volatile UDWord *SYSCON_ADDR_ = (UDWord *)0x100000;

    void
    FastShutdown()
    {
        *SYSCON_ADDR_ = 0x5555;
    }

    void
    FastReboot()
    {
        *SYSCON_ADDR_ = 0x7777;
    }
} // namespace vacui::kernel::hub

