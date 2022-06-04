#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;

};

