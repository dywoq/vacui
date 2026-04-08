// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#ifndef _VACUI_KERNEL_HUB_PANIC_HXX
#define _VACUI_KERNEL_HUB_PANIC_HXX

namespace vacui::kernel::hub
{
    [[noreturn]]
    void
    Panic(const char *msg) noexcept;
} // namespace vacui::kernel::hub

#endif

