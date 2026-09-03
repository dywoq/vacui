//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      BSL memory management interface types
//

#ifndef BSLMM_H
#define BSLMM_H

#include "bsldef.h"
#include "bslstat.h"

typedef bsl_ulong_t  bsl_handle_memory_size_t;
typedef bsl_ulong_t *bsl_handle_memory_pointer_t;

//
// Routine Description
//
//      A handle consisting of a memory pointer and its meta
//      information.
//
typedef struct bsl_memory_handle {
    bsl_handle_memory_size_t    size_in_bytes;
    bsl_handle_memory_pointer_t pointer;
} bsl_memory_handle_t;

#define BSL_MM_ERROR_OUT_OF_MEMORY 1
#define BSL_MM_ERROR_NULL_POINTER  2

//
// Routine Description
//
//      Allocates the memory size in bytes and returns handle with the
//      memory size and pointer.
//
// Parameters
//
//      memory_handle_dest  OUT
//
//          A required pointer to the destination memory handle. The function
//          writes the requested memory size and pointer to it.
//
//      size_in_bytes       IN
//
//          The required memory size.
//
// Error codes
//
//      BSL_STATUS_ERROR_CODE_OK
//
//          The operation was successful.
//
//      BSL_MM_ERROR_OUT_OF_MEMORY
//
//          There is no enough memory for allocation.
//
// Return
//
//      A status code.
//
typedef bsl_status_t (*bsl_mm_base_allocate_func)(
    bsl_memory_handle_t     *memory_handle_dest,
    bsl_handle_memory_size_t size_in_bytes
);

//
// Routine Description
//
//      Destroys the memory pointer, which is provided by the handle,
//      making it unusable.
//
// Parameters
//
//      memory_handle_source  IN
//
//          The memory handle, returned by the allocation function
//          (bsl_mm_base_allocate_func).
//
// Error codes
//
//      BSL_STATUS_ERROR_CODE_OK
//
//          The operation was successful.
//
//      BSL_MM_ERROR_NULL_POINTER
//
//          The memory_handle parameter or the pointer to the allocated memory
//          is null.
//
// Return
//
//      A status code.
//
typedef bsl_status_t (*bsl_mm_base_destroy_func)(
    const bsl_memory_handle_t *memory_handle_source
);

//
// Routine Description
//
//      Provides a set of base methods to manage memory.
//
typedef struct bsl_mm_base_iface {
    bsl_mm_base_allocate_func allocate;
    bsl_mm_base_destroy_func  destroy;
} bsl_mm_base_iface_t;

#endif
