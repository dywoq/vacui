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
//      Sets current video mode to the provided one (NewVideoMode).
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
// BIOS Interrupt
//
//      AH = 0x0F
//
HLB_VIDEO_MODE
HlbGetVideoMode();

//
// Routine Description
//
//      Prints the provided character into the screen. It works only if
//      the current mode is text mode.
//
// BIOS Interrupt
//
//      AH = 0x0E
//      AL = Character
//      BH = PageNumber
//
void
HlbVideoTeletypeOutput(
    VQ_ASCIICHAR Character,
    VQ_UBYTE     PageNumber
);

#endif
