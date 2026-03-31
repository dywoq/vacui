// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _ZERO_BIOS_VIDEO_H
#define _ZERO_BIOS_VIDEO_H

#include <zero/types.hxx>

namespace zero::boot::bios
{
    void
    SetVideoMode(UWord mode);

    UWord
    GetVideoMode();
} // namespace zero::boot::bios

#endif
