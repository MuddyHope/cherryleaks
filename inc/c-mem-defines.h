#ifndef C_MEM_DEFINES_H
#define C_MEM_DEFINES_H

#define TRUE 1
#define FALSE 0

typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;

}c_mem_entity;

#endif /*C_MEM_DEFINES_H*/