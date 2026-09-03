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

typedef const char *(bsl_meta_information_get_name_func)();
typedef const char *(bsl_meta_information_get_type_func)();

//
// Routine Description
//
//      An interface consisting of methods that provide information of
//      environment.
//
typedef struct bsl_meta_information_iface {
    bsl_meta_information_get_name_func get_name;
    bsl_meta_information_get_type_func get_type;
} bsl_meta_information_iface_t;

#endif
