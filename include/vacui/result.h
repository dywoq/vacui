// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#ifndef _VACUI_RESULT_H
#define _VACUI_RESULT_H

#include "abi/c.h"

#define VACUI_RESULT_DEF_C(name, errorType, valueType)                                                                 \
    VACUI_ABI_EXTERN_C struct name                                                                                     \
    {                                                                                                                  \
        errorType error;                                                                                               \
        valueType value;                                                                                               \
        bool ok;                                                                                                       \
    };                                                                                                                 \
    static struct name name##Ok(valueType value)                                                                       \
    {                                                                                                                  \
        return (struct name){.value = value, .ok = true};                                                              \
    }                                                                                                                  \
    static struct name name##Error(errorType error)                                                                    \
    {                                                                                                                  \
        return (struct name){.error = error, .ok = false};                                                             \
    }

#endif

