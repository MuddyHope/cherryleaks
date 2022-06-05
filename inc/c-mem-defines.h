#ifndef C_MEM_DEFINES_H
#define C_MEM_DEFINES_H

#define TRUE 1
#define FALSE 0

#define MALLOCATED 0
#define REALLOACTED 1
#define CALLOCATED 2
#define FREED 3

typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;
    uint8_t alloc_type;

}c_mem_entity;

#endif /*C_MEM_DEFINES_H*/