// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      This module defines the AAL exception abstraction layer structs.

#ifndef _VACUIP_AAL_EXCEPTION_H
#define _VACUIP_AAL_EXCEPTION_H

#include "../types.h"
#include "privilege.h"

// Generic exception codes
enum aal_exception_code : uint_t {
    AAL_EXCEPTION_PAGE_FAULT = 0,
    AAL_EXCEPTION_DATA_ACCESS_FAULT,
    AAL_EXCEPTION_ILLEGAL_INSTRUCTION,
    AAL_EXCEPTION_SOFTWARE_BREAKPOINT,
    AAL_EXCEPTION_ALIGNMENT_FAULT,
};

// A generic exception information.
struct aal_exception_info {
    aal_exception_code what;
    uint_t where;
    uint_t bad_memory_address;
    enum aal_privilege previous_privilege;
};

// A unified type alias for exception handler. It's passed a generic exception
// information.
typedef void (*aal_exception_handler)(struct aal_exception_info *info);

// An exception abstraction layer with function pointers,
// which allow you to set handler for various exceptions.
struct aal_exception_layer {
    void (*set_handler)(
        enum aal_exception_code code,
        aal_exception_handler handler
    );
};

#endif
