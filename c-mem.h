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

/** Add data to mem-block entity
 * 
 * @param amount - amount of bytes to be allocated
 * @param file  - name of teh file where allocation is done
 * @param line - line number where allocation is done
 * @param list - gobal list structure where memory data is stored 
 * @return pointer to allocated memory
 */
void* memory_data_malloc(size_t amount, char* file, size_t line, list *l)
{
    void* alloc_addr = malloc(amount);
    c_mem_entity block;

    block.address = alloc_addr;
    block.size = amount;
    block.file = file;
    block.line = line;
    list_push_back(GLOBAL_LIST, (void*)&block, sizeof(block));
    return alloc_addr;
}

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
#define realloc(n) start(GLOBAL_LIST) ? : realloc(n)
#define calloc(num, size) start(GLOBAL_LIST) ? : calloc(num, size)
#define free(addr) start(GLOBAL_LIST) ? : free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/