#include <kernel/types.h>
#define GDT_ENTRIES 3
#define __NEED_uintptr_t


struct gdt_entry{
    uint16 limit_lower;
    uint16 base_lower;
    uint8 base_middle;
    uint8 access_rights;
    uint8 flags_limit_higher;
    uint8 base_higher;
} __attribute__((packed));

struct gdt_description {
    uint16 limit;
    uint32 base;
} __attribute__((packed));

extern void gdt_install();

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_description gdt_desc;

int gdt_setup();