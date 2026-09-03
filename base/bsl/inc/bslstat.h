//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      BSL status type and struct definitions
//

#ifndef BSLSTAT_H
#define BSLSTAT_H

#include "bsldef.h"

typedef enum bsl_source_index : bsl_uint_t {
    bsl_source_index_none = 0,
    bsl_source_index_mm = 1,
} bsl_source_index_t;

typedef bsl_uint_t bsl_error_code_t;
#define BSL_STATUS_ERROR_CODE_OK (bsl_error_code_t)0

typedef struct bsl_status {
    bsl_source_index_t source_index;
    bsl_error_code_t   error_code;
} bsl_status_t;

#endif
