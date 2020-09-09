#include <kernel/descriptor_table/global_descriptor_table.h>

void gdt_set_entry(unsigned int pos, uint32 base, 
        uint32 limit, uint8 access_rights, uint8 flags){
            gdt[pos].base_lower = base & 0xffff;
            gdt[pos].base_middle = (base >> 16) & 0xff;
            gdt[pos].base_higher = (base >> 24) & 0xffff;

            gdt[pos].limit_lower = limit & 0xffff;
            gdt[pos].flags_limit_higher = ((flags << 4) & 0xf0) | ((limit >> 16) & 0x0f);
            gdt[pos].access_rights = access_rights;

            // IN normal you have to calculate the Bytes for every GDT Entry and then hard encode that
            //something for the next steps of out OS
        }


int gdt_setup(){
    gdt_desc.limit = GDT_ENTRIES * sizeof(struct gdt_entry) - 1;
    gdt_desc.base = (uint32) gdt;
    
    gdt_set_entry(0, 0, 0, 0, 0);
    gdt_set_entry(1, 0 , 0xffff, 0x9a, 0xcf);
    gdt_set_entry(2, 0,0xffff, 0x92, 0xcf);

    gdt_install();
    return 0;
}