#include <kernel/kernel.h>
#include <kernel/drivers/graphics/vga.h>
#include <kernel/loader/kernel_task.h>

void kernel_main() {
    start_task(DEFAULT_TASK);
    kinfo("Kernel ready\n");
}