// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/zero
//
// The project is not associated with Nintendo Co., Ltd.

#include <zero/debug/trace.h>

static size_t stack_top_ = 0;
static thread_local struct zr_debug_trace_loc stack_[ZR_DEBUG_TRACE_STACK_MAX] =
    {};

void zr_debug_trace_push(struct zr_debug_trace_loc loc) {
#if DEBUG
    if (stack_top_ >= ZR_DEBUG_TRACE_STACK_MAX) {
        return;
    }
    stack_[stack_top_] = loc;
    stack_top_++;
#endif
}

void zr_debug_trace_pop() {
#if DEBUG
    if (stack_top_ == 0) {
        return;
    }
    stack_[stack_top_] = (struct zr_debug_trace_loc){"", "", 0};
    stack_top_--;
#endif
}

[[nodiscard]] struct zr_debug_trace_loc *zr_debug_trace_stack() {
#if DEBUG
    return stack_;
#else
    return nullptr;
#endif
}

[[nodiscard]] struct zr_debug_trace_loc *zr_debug_trace_stack_last() {
#if DEBUG
    if (stack_top_ == 0) {
        return nullptr;
    }
    return &stack_[stack_top_ - 1];
#else
    return nullptr;
#endif
}
