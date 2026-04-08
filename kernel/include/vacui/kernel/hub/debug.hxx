// Copyright 2026 BellusTM - Apache License 2.0
// A part of https://github.com/bellustm/vacui

#ifndef _VACUI_KERNEL_HUB_DEBUG_HXX
#define _VACUI_KERNEL_HUB_DEBUG_HXX

#include <vacui/kernel/autoconf.h>
#include <vacui/kernel/utility/debug.hxx>

namespace vacui::kernel::hub::debug
{
    static constexpr bool
    IsEnabled() noexcept
    {
#if CONFIG_HUB_DEBUG
        return true;
#else
        return false;
#endif
    }

    static inline void
    LogC(char ch) noexcept
    {
        if constexpr (IsEnabled())
            utility::debug::LogC(ch);
    }

    static inline void
    LogStr(const char *str) noexcept
    {
        if constexpr (IsEnabled())
            utility::debug::LogStr(str);
    }
} // namespace vacui::kernel::hub::debug

#endif

