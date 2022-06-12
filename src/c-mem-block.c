#include "../inc/c-mem-block.h"

void block_replace_with(c_mem_entity* block,
                        void* addr, 
                        size_t s, 
                        char* fl, 
                        size_t l, 
                        uint8_t allc_t)
{
    block->address = addr;
    block->size = s;
    block->file = fl;
    block->line = l;
    block->alloc_type = allc_t;
}

c_mem_entity create_block()
{
    c_mem_entity block;
    block_replace_with(&block,
                       C_MEM_BLOCK_ADDR_INIT,
                       C_MEM_BLOCK_SIZE_INIT,
                       C_MEM_BLOCK_FILE_INIT,
                       C_MEM_BLOCK_LINE_INIT,
                       C_MEM_BLOCK_ALLOC_TYPE_INIT);               
    return block;
}

char * buffer_to_prt(int code)
{
    switch (code) 
    {                      
        case MALLOCATED:           
            return BUFFER_MAL;       
        case REALLOACTED:       
            return BUFFER_REA;   
        case CALLOCATED:       
            return BUFFER_CAL;
        case FREED:
            return BUFFER_FRE; 
    }            
    return BUFFER_NULL;
}

int c_mem_print_block(c_mem_entity * block)
{
    return 1;
}