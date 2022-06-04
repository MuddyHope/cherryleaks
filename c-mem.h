#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "list.h"

#ifndef C_MEM_H
#define C_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

typedef struct
{
    void* address;
    size_t size;
    char* file;
    size_t line;

}c_mem_entity;

list GLOBAL_LIST = 0;

uint8_t _start(list l)
{
    if(!l)
    {
        return 0;
    } else 
    {
        return 1;
    }

}

/** Initialize the program and start recording
 * 
 * 
 */
#define START \
    GLOBAL_LIST = make_list();

/** End recording, print all leftovers
 * 
 * 
 */
#define END_PRINT

/** End recording, print all memory data
 *  
 * 
 */
#define END_PRINT_ALL


#define test if(_start(GLOBAL_LIST)) printf("Inside\n")
#define malloc(n) malloc(n)
#define realloc(n) realloc(n)
#define calloc(num, size) calloc(num, size)
#define free(addr) free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/