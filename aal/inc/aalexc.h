/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:
    Defines the AAL exception abstraction layer structs.
*/

#ifndef _AALEXC_H
#define _AALEXC_H

#include <aaltier.h>
#include <vqtypes.h>

/*
Description:
    Generic exception codes
*/
typedef uint_t aal_exc_code_t;
#define AAL_EXC_PAGE_FAULT          (aal_exc_code_t)0
#define AAL_EXC_DATA_ACCESS_FAULT   (aal_exc_code_t)1
#define AAL_EXC_ILLEGAL_INSTRUCTION (aal_exc_code_t)2
#define AAL_EXC_SOFTWARE_BREAKPOINT (aal_exc_code_t)3
#define AAL_EXC_ALIGNMENT_FAULT     (aal_exc_code_t)4

/*
Description:
    A generic exception information.
*/
struct aal_exc_info
{
    aal_exc_code_t what;
    uint_t         where;
    uint_t         bad_memory_address;
    aal_tier_t     previous_tier;
};

/*
Description:
    A unified type alias for exception handler. It's passed a generic
    exception information.
*/
typedef void (*aal_exc_handler)(struct aal_exc_info *info);

/*
Description:
    An exception abstraction layer with function pointers,
    which allow you to set handler for various exceptions.
*/
struct aal_exc_layer
{
    void (*set_handler)(
        aal_exc_code_t  code,
        aal_exc_handler handler
    );
};

#endif
