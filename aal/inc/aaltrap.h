// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      Defines the AAL trap abstraction layer structs.
//      WARNING: It doesn't contain exceptions layer, only
//      process-caused traps. The exception layer is defined in
//      <aalexc.h>.

#ifndef _AALTRAP_H
#define _AALTRAP_H

#include <vqtypes.h>

// Description:
//
//      A type alias for trap handler.
typedef void (*aal_trap_handler_t)(void *data);

// Description:
//
//      Defines an error enumerations. Returned by aal_trap_layer functions.
typedef ushort_t aal_trap_err_t;
#define AAL_TRAP_OK (aal_trap_err_t)0
// The given ID overflows the limit.
#define AAL_TRAP_ID_OVERFLOW (aal_trap_err_t)1
// You have reached the limit of trap handlers.
#define AAL_TRAP_LIMIT_REACHED (aal_trap_err_t)2

// Description:
//
//      Unified generic AAL traps management layer.
struct aal_trap_layer
{
    // Description:
    //
    //      Sets a trap handler.
    //      The AAL uses this formula to decide where to put a trap handler:
    //
    //              Position = Base software ID number + id
    //
    // Return:
    //
    //      See `aal_trap_err` for errors.
    aal_trap_err_t (*set_handler)(
        ubyte_t            id,
        aal_trap_handler_t handler
    );
};

#endif
