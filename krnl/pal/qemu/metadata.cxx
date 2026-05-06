// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui
//
// Description:
//
// QEMU platform implementation of vacui/pal/metadata.h

#include <vacui/pal/metadata.h>

namespace vacui::pal {
    const char *get_name() noexcept { return "qemu"; }
    id          get_id() noexcept { return id::qemu; }
} // namespace vacui::pal
