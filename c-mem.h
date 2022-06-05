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


#define test if(list_is_null(GLOBAL_LIST)) printf("Inside\n")
#define malloc(n) list_is_null(GLOBAL_LIST) ? memory_data_malloc(n, __FILE__, __LINE__, GLOBAL_LIST) : malloc(n)
#define realloc(ptr, n) list_is_null(GLOBAL_LIST) ? memory_data_realloc(ptr, n __FILE__, __LINE__, GLOBAL_LIST) : realloc(ptr, n)
#define calloc(num, size) list_is_null(GLOBAL_LIST) ? : calloc(num, size)
#define free(addr) list_is_null(GLOBAL_LIST) ? : free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/