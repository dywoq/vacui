// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module description:
//
//      This module defines the AAL trap abstraction layer structs.
//      WARNING: It doesn't contain exception layer, only
//      process-caused traps. The exception layer is defined in
//      <vacuip/aal/exception.h>.

#ifndef _VACUIP_AAL_TRAP_H
#define _VACUIP_AAL_TRAP_H

#include "../types.h"

// A type alias for trap handler.
typedef void (*aal_trap_handler_t)(void *data);

enum aal_trap_err : ushort_t {
    AAL_TRAP_OK = 0,

    // The given ID overflows the limit.
    AAL_TRAP_ID_OVERFLOW,

    // You have reached the limit of trap handlers.
    AAL_TRAP_LIMIT_REACHED,
};

struct aal_trap_layer {
    // Sets a trap handler.
    // The AAL uses this formula to decide where to put a trap handler:
    //
    //      Position = Base software ID number + id
    //
    // See `aal_trap_err` for errors.
    aal_trap_err (*set_handler)(
        ubyte_t id,
        aal_trap_handler_t handler
    );
};

#endif
