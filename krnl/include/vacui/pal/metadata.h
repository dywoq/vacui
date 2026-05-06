// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// Kernel PAL metadata functions

#ifndef _VACUI_PAL_METADATA_H
#define _VACUI_PAL_METADATA_H

namespace vacui::pal {
    enum class id {
        qemu = 1,
    };
    const char *get_name() noexcept;
    id          get_id() noexcept;
} // namespace vacui::pal

#endif
