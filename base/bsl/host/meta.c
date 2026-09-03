//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Routine Description
//
//      An implementation of the meta information interface
//

#include "bslhost.h"
#include "bslmeta.h"

static const char *host_get_name_() { return "HOST"; }

static const char *host_get_type_() {
#if _TOOLCHAIN_LINUX && _TOOLCHAIN_X86_64
    return "LINUX-X86_64";
#endif
    return "UNKNOWN";
}

static bsl_meta_information_iface_t meta_information_ = {
    .get_name = host_get_name_,
    .get_type = host_get_type_,
};

bsl_meta_information_iface_t *bsl_host_get_meta_information_iface() {
    return &meta_information_;
}
