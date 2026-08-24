//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      HLB video services
//

#ifndef HLBVID_H
#define HLBVID_H

#include <vqdef.h>

typedef VQ_UBYTE HLB_VIDEO_MODE, *PHLB_VIDEO_MODE;

//
// Routine Description
//
//      Sets current video mode to the provided one.
//
// Parameters
//
//      NewVideoMode
//      - The new video mode. It must match the video modes specified in the
//      documentation.
//
// BIOS Interrupt
//
//      AH = 0x00
//      AL = NewVideoMode
//
void
HlbSetVideoMode(HLB_VIDEO_MODE NewVideoMode);

//
// Routine Description
//
//      Gets current video mode.
//
// Parameters
//
//      NewVideoMode
//      - The new video mode. It must match the video mode values specified
//      in the documentation.
//
// BIOS Interrupt
//
//      AH = 0x0F
//
HLB_VIDEO_MODE
HlbGetVideoMode();

#endif
