// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero

#ifndef _RESULT_ERROR_H
#define _RESULT_ERROR_H

#include <std/types.h>

enum result_err_code : ubyte_t {
    RESULT_ERR_OK = 0,
    RESULT_ERR_FAILED = 1,
    RESULT_ERR_NULL_PTR = 2,
};

struct result_err {
    enum result_err_code code;
    const char *additional;
};

#define RESULT_IS_ERR(err) (err != RESULT_ERR_OK)
#define RESULT_IS_OK(err) (err == RESULT_ERR_OK)

#define RESULT_NEW(num, str)                                                   \
    (struct result_err) { .code = num, .additional = str }

#endif
