//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      BSL host operating system-specific types, macros, constants
//      and functions
//

#ifndef BSLHOST_H
#define BSLHOST_H

#include "bslmeta.h"
#include "bslmm.h"

//
// Routine Description
//
//      Returns a pointer to the host implementation of the
//      bsl_meta_information_iface_t interface.
//
bsl_meta_information_iface_t *bsl_host_get_meta_information_iface();

//
// Routine Description
//
//      Returns a pointer to the host implementation of the
//      bsl_mm_base_iface_t interface.
//
bsl_mm_base_iface_t *bsl_host_get_mm_base_ifacec();

#endif
