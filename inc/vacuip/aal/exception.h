// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      This module defines the AAL exception abstraction layer structs.

#ifndef _VACUIP_AAL_EXCEPTION_H
#define _VACUIP_AAL_EXCEPTION_H

#include "../types.h"

// A generic exception information.
struct aal_exception_info {
    uint_t what;
    uint_t where;
    uint_t bad_memory_address;
    uint_t previous_privilege_code;
};

// A unified type alias for exception handler. It's passed a generic exception
// information.
typedef void (*aal_exception_handler)(struct aal_exception_info *info);

// An exception abstraction layer with function pointers,
// which allow you to set handler for various exceptions.
struct aal_exception_layer {
    void (*set_page_fault_handler)(aal_exception_handler handler);
    void (*set_protection_fault)(aal_exception_handler handler);
    void (*set_illegal_instr_fault)(aal_exception_handler handler);
};

#endif
