//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      This header provides debugging functionality.
//
// Environment
//
//      VQBoot primary stage
//

#ifndef DEBUG_H
#define DEBUG_H

#include "print.h"

#if DEBUG
#define DebugPrintMsg(Message) PrimaryPrintMsg("DEBUG: " Message)
#else
#define DebugPrintMsg(Message) ((void)0)
#endif

#endif
