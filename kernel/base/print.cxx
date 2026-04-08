// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#include <vacui/types.hxx>

namespace vacui::kernel::base
{
    void
    PrintC(char ch) noexcept
    {
        volatile UByte *videoRam = (volatile UByte *)0x10000000;
        *videoRam = ch;
    }

    void
    PrintStr(const char *str) noexcept
    {
        for (const char *p = str; *p != '\0'; ++p)
            PrintC(*p);
    }
} // namespace vacui::kernel::base

