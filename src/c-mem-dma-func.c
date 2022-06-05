#include "../inc/c-mem-dma-func.h"


void* memory_data_malloc(size_t amount, char* file, size_t line, list *l)
{
    void* alloc_addr = malloc(amount);
    c_mem_entity block;

    block.address = alloc_addr;
    block.size = amount;
    block.file = file;
    block.line = line;
    printf("LINE: %u\nFILE: %s\namount:%u\n", line, file, amount);
    list_push_back(GLOBAL_LIST, (void*)&block, sizeof(block));
    return alloc_addr;
}

void* memory_data_realloc(void* ptr, size_t amount, char* file, size_t line, list *l){}