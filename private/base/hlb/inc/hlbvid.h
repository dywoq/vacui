//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      HLB Video master header
//

#ifndef HLBVID_H
#define HLBVID_H

#include <vqdef.h>

typedef UBYTE HLB_VIDEO_MODE;
typedef BYTE  HLB_TELETYPECHAR;

//
// Routine Description
//
//      Sets the current video mode to the provided one. See
//      https://www.ctyme.com/intr/rb-0069.htm for available video modes.
//
// Parameters
//
//      VideoMode
//
//          The new video mode.
//
void
HlbSetVideoMode(HLB_VIDEO_MODE VideoMode);

//
// Routine Description
//
//      Prints the provided character using the teletype output interrupt.
//      See more information: https://www.ctyme.com/intr/rb-0106.htm
//
//
// Parameters
//
//      Character
//
//          The character to print.
//
void
HlbVideoTeletypeOutput(HLB_TELETYPECHAR Character);

#endif
