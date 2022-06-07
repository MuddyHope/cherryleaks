#include <stdlib.h>
#include <stdin.h>
#include "c-mem-defines.h"

#ifndef C_MEM_BLOCK_H
#define C_MEM_BLOCK_H

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
void block_replace_with(c_mem_entity* block,
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

/** Print data corresponding to mem-block
 * 
 * 
 * @param block - mem block to be printed
 * @return 1 if success or 0 if error occurs
 */
uint8_t c_mem_print_block(c_mem_entity * block);

#endif /*C_MEM_BLOCK_H*/