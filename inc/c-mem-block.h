#include <stdlib.h>

#ifndef C_MEM_BLOCK_H
#define C_MEM_BLOCK_H

typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;
    uint8_t alloc_type;

}c_mem_entity;

#endif /*C_MEM_BLOCK_H*/