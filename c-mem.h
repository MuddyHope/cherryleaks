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
#include "list.h"

#ifndef C_MEM_H
#define C_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE 0

#define BUFFER_INTERNAL_SIZE 1500

/**
 * @brief
 *
 */
#define MALLOCATED 0
#define REALLOACTED 1
#define CALLOCATED 2
#define FREED 3

/**
 * @brief
 *
 */
#define BUFFER_MAL \
    "malloc"
#define BUFFER_REA \
    "realloc"
#define BUFFER_CAL \
    "calloc"
#define BUFFER_FRE \
    "freed"
#define BUFFER_NULL \
    "Could not read memory block."

#define C_MEM_BLOCK_ADDR_INIT NULL
#define C_MEM_BLOCK_SIZE_INIT 0
#define C_MEM_BLOCK_FILE_INIT NULL
#define C_MEM_BLOCK_LINE_INIT 0
#define C_MEM_BLOCK_ALLOC_TYPE_INIT 255

typedef struct c_mem_entity
{
    void* address;
    size_t size;
    char* file;
    size_t line;
    uint8_t alloc_type;

}c_mem_entity;

/** Replace values in current block
 *
 * @param block - entity where data whould be replaced
 * @param addr - addr to be replaced
 * @param s - size to be replaced
 * @param fl - filename to be replaced
 * @param l - line to be replaced
 * @param allc_t - allocation type to be replaced
 */
void block_value(c_mem_entity* block,
                 void* addr,
                 size_t s,
                 char* fl,
                 size_t l,
                 uint8_t allc_t);

/**
 * @brief Create an empty block object
 *
 * @return c_mem_entity with initial values
 */
c_mem_entity create_block();

/** Generate data string corresponding to mem-block
 *
 *
 * @param block - mem block to be printed
 * @return 1 if success or 0 if error occurs
 */
int c_mem_generate_message(c_mem_entity * block, char * buffer);


/** Generate buffer according to type
 *
 * @param code - alloc_type
 * @return char* - buffer
 */
char * buffer_to_prt(int code);

void c_mem_emit_data(list* l, uint8_t flag);

/** Add data to mem-block entity
 *
 * @param amount - amount of bytes to be allocated
 * @param file  - name of the file where allocation is done
 * @param line - line number where allocation is done
 * @param list - global list structure where memory data is stored
 * @return pointer to allocated memory
 */
void* memory_data_malloc(size_t amount, char* file, size_t line, list *l);

/** Reallocate memory in the mem-block entity
 *
 *
 * @param ptr   - This is the pointer to a memory block previously allocated with malloc, calloc or realloc to be reallocated.
 * @param amount - the amount of bytes to be reallocated
 * @param file  - name of the file where allocation is done
 * @param line - line number where allocation is done
 * @param list - global list structure where memory data is stored
 * @return pointer to reallocated memory
 */
void* memory_data_realloc(void* ptr, size_t amount, char* file, size_t line, list *l);

/** Add data to mem-block entity with calloc
 *
 *
 * @param amount - amount of data-units to be allocated
 * @param size - size of a data-unit
 * @param file  - name of the file where allocation is done
 * @param line - line number where allocation is done
 * @param list - global list structure where memory data is stored
 * @return pointer to allocated memory
 */
void* memory_data_calloc(size_t amount, size_t size, char* file, size_t line, list* l);

/** Free mem-blovk entity
 *
 *
 * @param ptr - pointer to allocated memory
 * @param list - global list structure where memory data is stored
 */
void memory_data_free(void* ptr, char* file, size_t line, list* l);

static list* GLOBAL_LIST = NULL;

/** Initialize the program and start recording
 * 
 */
#define C_MEM_START  \
    list l = make_list(); \
    GLOBAL_LIST = &l; 


/** End recording, print all leftovers
 *  
 */
#define C_MEM_END_PRINT_LEFT \
    c_mem_emit_data(GLOBAL_LIST, FALSE); \
    list_clear(GLOBAL_LIST); \

/** End recording, print all memory data
 *  
 */
#define C_MEM_END_PRINT_ALL \
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