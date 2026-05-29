// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      Defines the AAL tier definitions.

#ifndef _AALTIER_H
#define _AALTIER_H

#include <vqtypes.h>

// Description:
//
//      Defines a AAL tier enumeration. Tier word is synonym to:
//          Rings (x86-specific)
//          Privileges
enum aal_tier : ubyte_t
{
    AAL_TIER_KERNEL = 0,
    AAL_TIER_USER,
};

#endif
