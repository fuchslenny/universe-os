#include <kernel/loader/kernel_task.h>
#include <kernel/loader/kernel_loader.h>

void start_task(uint8 task_type) {
    if (task_type != EVERY_AVAILABLE_TASK && (kernel_on != 1 || kernel_paused == 1)) {
        while (kernel_on != 1);
        while (kernel_paused == 1);
    }
}