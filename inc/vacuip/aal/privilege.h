// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      This module defines the AAL privilege definitions.

#ifndef _VACUIP_AAL_PRIVILEGE_H
#define _VACUIP_AAL_PRIVILEGE_H

#include "../types.h"

enum aal_privilege : ubyte_t {
    AAL_PRIVILEGE_KERNEL = 0,
    AAL_PRIVILEGE_USER,
};

#endif
