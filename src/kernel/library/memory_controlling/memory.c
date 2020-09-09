#include <kernel/library/memory_controlling/memory.h>

void* memset(void *begin, int value, int size) {
    unsigned char *p = begin; 
    while (begin && size > 0) {
        *p = value;
        begin++;
        size--;
    }
    return begin;
}
