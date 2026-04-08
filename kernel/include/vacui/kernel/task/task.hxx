// Copyright 2026 dywoq - Apache License 2.0
// A part of https://github.com/dywoq/vacui

#ifndef _VACUI_KERNEL_TASK_TASK_HXX
#define _VACUI_KERNEL_TASK_TASK_HXX

#include <vacui/types.hxx>

namespace vacui::kernel::task
{
    enum class TaskState
    {
        READY,
        DONE,
        BLOCKED,
    };

    using TaskID = UDWord;
    using TaskFn = void (*)(TaskID);

    struct Task
    {
        TaskID id;
        TaskFn fn;
        TaskState state;
        bool unblockTrigger;
    };

    [[nodiscard]] inline static constexpr Task
    CreateDefaultTask() noexcept
    {
        return {0, nullptr, TaskState::READY, false};
    }
} // namespace vacui::kernel::task

#endif

