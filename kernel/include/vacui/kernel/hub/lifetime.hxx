// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#ifndef _VACUI_KERNEL_HUB_LIFETIME_HXX
#define _VACUI_KERNEL_HUB_LIFETIME_HXX

namespace vacui::kernel::hub
{

    // These functions do not properly exit
    // and kill kernel immediately.

    void
    FastShutdown() noexcept;

    void
    FastReboot() noexcept;
} // namespace vacui::kernel::hub

#endif

