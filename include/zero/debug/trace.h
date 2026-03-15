// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero
//
// The project is not associated with Nintendo Co., Ltd.

#ifndef _ZERO_DEBUG_TRACE_H
#define _ZERO_DEBUG_TRACE_H

// Header overview
//
// Debug trace stack management

#include <stddef.h>

// Represents a debug trace location.
//
// Notes:
// - It's not recommended to fill it automatically,
//   as ZR_DEBUG_TRACE_GUARD macro already does this for you.
struct zr_debug_trace_loc {
    const char *file;
    const char *func;
    int line;
};

// A max size of debug trace locations per thread.
constexpr int ZR_DEBUG_TRACE_STACK_MAX = 64;

// Pushes a new location to the thread-local stack.
//
// Parameters:
// - `loc`: A location to push.
//
// Notes:
// - It's not recommended to call it manually.
//   Use ZR_DEBUG_TRACE_GUARD macro.
//
// - Works only if DEBUG macro is 1.
void zr_debug_trace_push(struct zr_debug_trace_loc loc);

// Pops the last pushed location from the thread-local stack.
//
// Notes:
// - It's not recommended to call it manually.
//   Use ZR_DEBUG_TRACE_GUARD macro.
//
// - Works only if DEBUG macro is 1.
void zr_debug_trace_pop();

// Returns the thread-local debug trace stack.
// Max size of elements is ZR_DEBUG_TRACE_STACK_MAX.
//
// Notes:
// - Returns nullptr if DEBUG macro isn't 1.
//
// - Call zr_debug_trace_stack_top to get the current
//   size of stack to iterate over stack.
[[nodiscard]] struct zr_debug_trace_loc *zr_debug_trace_stack();

// Returns the latest location from thread-local debug trace stack.
//
// Notes:
// - Returns nullptr if DEBUG macro isn't 1, or there are no locations pushed.
[[nodiscard]] struct zr_debug_trace_loc *zr_debug_trace_stack_last();

#if DEBUG
inline void zr___debug_trace_dummy(void *) { zr_debug_trace_pop(); }
// Automatically pushes location, and pops it when the guard is out of scope.
//
// Notes:
// - Works only if DEBUG macro is 1.
#define ZR_DEBUG_TRACE_GUARD()                                                 \
    zr_debug_trace_push(                                                       \
        (struct zr_debug_trace_loc){__FILE_NAME__, __FUNCTION__, __LINE__});   \
    [[gnu::cleanup(                                                            \
        zr___debug_trace_dummy)]] void *__debug_trace_guard_cleanup = nullptr
#else
#define ZR_DEBUG_TRACE_GUARD()
#endif

#endif
