#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifndef C_MEM_H
#define C_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;

};

#define START 
#deifne END

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/