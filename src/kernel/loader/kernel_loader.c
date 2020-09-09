#include <kernel/loader/kernel_loader.h>
#include <kernel/drivers/graphics/vga.h>
#include <kernel/descriptor_table/global_descriptor_table.h>
#include <kernel/descriptor_table/interrupt_descriptor_table.h>
#include <kernel/library/memory_controlling/memory.h>

unsigned short kernel_on = 0;
unsigned short kernel_paused = 0;
struct load_type load_types[TYPE_AND_ENTRY_LENGTH] = {
        {.name="GRAPHIC_VGA_DRIVER", .function=&load_vga_driver},
        {.name="GLOBAL_DESCRIPTOR_TABLE", .function=&gdt_setup},
        {.name="INTERRUPT_DESCRIPTOR_TABLE", .function=&idt_install},
        {.name="INTERRUPT_SERVICE_ROUTINES", .function=&isrs_install},
};
struct load_entry load_entrys[TYPE_AND_ENTRY_LENGTH];

void print_entry(struct load_entry *loadEntry) {
    kinfo("[LOADER]");
    kinfo(" Loading Module ");
    kinfo(loadEntry->type.name);
    printc(' ', &default_color);
    switch (loadEntry->status) {
        case LOAD_STATUS_UNKNOW: setPointerToEndOfLine(8);kunknow("[UNKNOW]"); break;
        case LOAD_STATUS_IN_PROGRESS: setPointerToEndOfLine(13);kwarning("[IN_PROGRESS]"); break;
        case LOAD_STATUS_ERROR: setPointerToEndOfLine(7);kerror("[ERROR]"); break;
        case LOAD_STATUS_SUCCESS: setPointerToEndOfLine(9);ksuccess("[SUCCESS]"); break;
        default:
            kerror("[ERROR]");
    }
    printc('\n', &default_color);
}

void kernel_panic_loader() {
    kerror("One of the loaders has status code ERROR or an error has been occured\n");
    kerror("[KERNEL_PANIC] The kernel stops here. Shut down and try again\n");
    while (1);
}

void kernel_panic(char *str) {
    kerror("An error has been occured: ");

    kerror(str);
    printn();
    kernel_panic_loader();
}

void start_loading() {
    int error_count = 0;
    for (int i=0; i < TYPE_AND_ENTRY_LENGTH; i++) {
        load_entrys[i] = (struct load_entry) {.type=load_types[i], .status=LOAD_STATUS_IN_PROGRESS};
        int status_code = load_types[i].function();
        if (status_code == 0) {
            load_entrys[i] = (struct load_entry) {.type=load_types[i], .status = LOAD_STATUS_SUCCESS};
        } else if (status_code < 0) {
            load_entrys[i] = (struct load_entry) {.type=load_types[i], .status = LOAD_STATUS_ERROR};
            error_count++;
        } else {
            load_entrys[i] = (struct load_entry) {.type=load_types[i], .status = LOAD_STATUS_UNKNOW};
        }
        print_entry(&load_entrys[i]);
    }
    if (error_count > 0) {
        kernel_on = 0;
        kernel_panic_loader();
    } else {
        kernel_on = 1;
    }
}
