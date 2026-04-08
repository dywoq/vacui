// Copyright 2026 BellusTM - Apache License 2.0
// A part of https://github.com/bellustm/vacui

#ifndef _VACUI_KERNEL_UTILITY_DEBUG_HXX
#define _VACUI_KERNEL_UTILITY_DEBUG_HXX

#include <vacui/kernel/autoconf.h>
#include <vacui/kernel/base/print.hxx>

namespace vacui::kernel::utility::debug
{
    [[nodiscard]] static constexpr bool
    IsEnabled() noexcept
    {
#if CONFIG_UTILITY_DEBUG
        return true;
#else
        return false;
#endif
    }

    static inline void
    LogC(char ch) noexcept
    {
        if constexpr (IsEnabled())
        {
            base::PrintStr("DEBUG: ");
            base::PrintC(ch);
        }
    }

    static inline void
    LogStr(const char *str) noexcept
    {
        if constexpr (IsEnabled())
        {
            base::PrintStr("DEBUG: ");
            base::PrintStr(str);
        }
    }
} // namespace vacui::kernel::utility::debug

#endif

