#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "inc/list.h"
#include "inc/c-mem-defines.h"

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

list* GLOBAL_LIST = 0;

/** Check the initialization of a list
 * 
 * @param l - new list entity
 * @return true if list was declared. else false 
 */
uint8_t start(list* l)
{
    if(!l)
    {
        return FALSE;
    } else 
    {
        return TRUE;
    }

}

/** Initialize the program and start recording
 * 
 */
#define START { \
    list l = make_list(); \
    GLOBAL_LIST = &l; \
}

/** End recording, print all leftovers
 *  
 */
#define END_PRINT

/** End recording, print all memory data
 *  
 */
#define END_PRINT_ALL


#define test if(start(GLOBAL_LIST)) printf("Inside\n")
#define malloc(n) malloc(n)
#define realloc(n) realloc(n)
#define calloc(num, size) calloc(num, size)
#define free(addr) free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/