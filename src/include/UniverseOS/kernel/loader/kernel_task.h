#ifndef UNIVERSEOS_KERNEL_TASK_H
#define UNIVERSEOS_KERNEL_TASK_H

#include <kernel/types.h>

enum task_types {
    DEFAULT_TASK,
    EXCEPTION_TASK,
    INTERRUPT_TASK,
    ERROR_TASK,
    HIGH_TASK,
    EVERY_AVAILABLE_TASK // started too if kernel stops
};

void start_task(uint8 task_type);

#endif //UNIVERSEOS_KERNEL_TASK_H
