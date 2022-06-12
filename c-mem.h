/**
 * @file c-mem.h
 * @author Vasily Davydov
 * @brief General c-mem lib header file
 * @version 0.1
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "inc/list.h"
#include "inc/c-mem-defines.h"
#include "inc/c-mem-dma-func.h"
#include "inc/c-mem-block.h"

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
#define END_PRINT_LEFT \
    c_mem_emit_data(GLOBAL_LIST, FALSE); \
    list_clear(GLOBAL_LIST); \

/** End recording, print all memory data
 *  
 */
#define END_PRINT_ALL \
    c_mem_emit_data(GLOBAL_LIST, TRUE); \
    list_clear(GLOBAL_LIST); \

#define malloc(n) list_is_null(GLOBAL_LIST) ? memory_data_malloc(n, __FILE__, __LINE__, GLOBAL_LIST) : malloc(n)
#define realloc(ptr, n) list_is_null(GLOBAL_LIST) ? memory_data_realloc(ptr, n, __FILE__, __LINE__, GLOBAL_LIST) : realloc(ptr, n)
#define calloc(n, size) list_is_null(GLOBAL_LIST) ? memory_data_calloc(n, size, __FILE__, __LINE__, GLOBAL_LIST) : calloc(n, size)
#define free(addr) list_is_null(GLOBAL_LIST) ? memory_data_free(addr, __FILE__, __LINE__, GLOBAL_LIST) : free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/