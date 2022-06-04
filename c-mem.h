#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "list.h"

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

list* global = NULL;

/** Initialize the program and start recording
 * 
 * 
 */
#define START global = &make_list();

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



#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/