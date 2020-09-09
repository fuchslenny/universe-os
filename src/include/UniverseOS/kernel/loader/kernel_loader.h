#ifndef UNIVERSEOS_KERNEL_LOADER_H
#define UNIVERSEOS_KERNEL_LOADER_H

#define PRINT_PREFIX "[LOADER]"
#define TYPE_AND_ENTRY_LENGTH 4
// Load Status
#define LOAD_STATUS_UNKNOW 0
#define LOAD_STATUS_IN_PROGRESS 1
#define LOAD_STATUS_ERROR 2
#define LOAD_STATUS_SUCCESS 3

typedef int load_function();

struct load_type {
    char *name;
    load_function *function;
};

struct load_entry {
    struct load_type type;
    int status;
};

extern struct load_type load_types[];
extern struct load_entry load_entrys[];

unsigned short kernel_on;
unsigned short kernel_paused;
void print_entry(struct load_entry *loadEntry);
void kernel_panic_loader();
void kernel_panic(char *str);
extern void start_loading();

#endif //UNIVERSEOS_KERNEL_LOADER_H
