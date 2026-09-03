//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      An implementation of the memory management interfaces
//

#include "bslmm.h"
#include "bslstat.h"

#include <stdlib.h>

static bsl_status_t mm_base_allocate_(
    bsl_memory_handle_t     *memory_handle_dest,
    bsl_handle_memory_size_t size_in_bytes
) {
    //
    // Initialize the status code
    //

    bsl_status_t status = {0};
    status.source_index = bsl_source_index_mm;

    //
    // Routine checks
    //

    if (!memory_handle_dest) {
        status.error_code = BSL_MM_ERROR_NULL_POINTER;
        return status;
    }

    //
    // Allocation itself
    //

    void *pointer = malloc(size_in_bytes);
    if (!pointer) {
        status.error_code = BSL_MM_ERROR_OUT_OF_MEMORY;
        return status;
    }

    //
    // Fill the memory handle
    //

    memory_handle_dest->size_in_bytes = size_in_bytes;
    memory_handle_dest->pointer = pointer;

    return status;
}

static bsl_status_t mm_base_destroy_(bsl_memory_handle_t *memory_handle_dest) {
    //
    // Initialize the status code
    //

    bsl_status_t status = {0};
    status.source_index = bsl_source_index_mm;

    //
    // Routine checks
    //

    if (!memory_handle_dest || !memory_handle_dest->pointer) {
        status.error_code = BSL_MM_ERROR_NULL_POINTER;
        return status;
    }

    //
    // Free the pointer
    //

    free(memory_handle_dest->pointer);
    memory_handle_dest->pointer = 0;
    memory_handle_dest->size_in_bytes = 0;

    return status;
}

static bsl_mm_base_iface_t mm_base_iface_ = {
    .allocate = mm_base_allocate_,
    .destroy = mm_base_destroy_,
};

bsl_mm_base_iface_t *bsl_host_get_mm_base_ifacec() { return &mm_base_iface_; }
