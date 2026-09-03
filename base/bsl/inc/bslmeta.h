//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      BSL meta information interface
//

#ifndef BSLMETA_H
#define BSLMETA_H

//
// Routine Description
//
//      An interface consisting of methods that provide information of
//      environment.
//
typedef struct bsl_meta_information_iface {
    const char *(get_name)();
    const char *(get_type)();
} bsl_meta_information_iface_t;

#endif
