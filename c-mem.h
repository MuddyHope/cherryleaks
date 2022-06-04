#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifndef C_MEM_H
#define C_MEM_H



typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;

};

#endif /*C_MEM_H*/