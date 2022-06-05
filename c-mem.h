#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "inc/list.h"
#include "inc/c-mem-defines.h"
#include "inc/c-mem-dma-func.h"

#ifndef C_MEM_H
#define C_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

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

list* GLOBAL_LIST = NULL;

/** Initialize the program and start recording
 * 
 */
#define START  \
    list l = make_list(); \
    GLOBAL_LIST = &l; 


/** End recording, print all leftovers
 *  
 */
#define END_PRINT

/** End recording, print all memory data
 *  
 */
#define END_PRINT_ALL


#define test if(start(GLOBAL_LIST)) printf("Inside\n")
#define malloc(n) start(GLOBAL_LIST) ? memory_data_malloc(n, __FILE__, __LINE__, GLOBAL_LIST) : malloc(n)
#define realloc(ptr, n) start(GLOBAL_LIST) ? memory_data_realloc(ptr, n __FILE__, __LINE__, GLOBAL_LIST) : realloc(ptr, n)
#define calloc(num, size) start(GLOBAL_LIST) ? : calloc(num, size)
#define free(addr) start(GLOBAL_LIST) ? : free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/