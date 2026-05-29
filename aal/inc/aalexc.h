// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Description:
//
//      Defines the AAL exception abstraction layer structs.

#ifndef _AALEXC_H
#define _AALEXC_H

#include <aaltier.h>
#include <vqtypes.h>

// Description:
//
//      Generic exception codes
enum aal_exc_code : uint_t {
    AAL_EXC_PAGE_FAULT = 0,
    AAL_EXC_DATA_ACCESS_FAULT,
    AAL_EXC_ILLEGAL_INSTRUCTION,
    AAL_EXC_SOFTWARE_BREAKPOINT,
    AAL_EXC_ALIGNMENT_FAULT,
};

// Description:
//
//      A generic exception information.
struct aal_exc_info {
    enum aal_exc_code what;
    uint_t where;
    uint_t bad_memory_address;
    enum aal_tier previous_tier;
};

// Description:
//
//      A unified type alias for exception handler. It's passed a generic
//      exception information.
typedef void (*aal_exc_handler)(struct aal_exc_info *info);

// Description:
//
//      An exception abstraction layer with function pointers,
//      which allow you to set handler for various exceptions.
struct aal_exc_layer {
    void (*set_handler)(
        enum aal_exc_code code,
        aal_exc_handler handler
    );
};

#endif
