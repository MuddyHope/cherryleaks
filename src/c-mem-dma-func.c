#include "../inc/c-mem-dma-func.h"


void* memory_data_malloc(size_t amount, char* file, size_t line, list *l)
{
    void* alloc_addr = malloc(amount);
    c_mem_entity block;

    block.address = alloc_addr;
    block.size = amount;
    block.file = file;
    block.line = line;
    list_push_back(l, (void*)&block, sizeof(block));
    return alloc_addr;
}

void* memory_data_realloc(void* ptr, size_t amount, char* file, size_t line, list *l)
{
    void* alloc_addr;
    c_mem_entity* buffer;
    if (ptr == NULL) 
    {
        alloc_addr = malloc(amount);
    }else
    {
        alloc_addr = realloc(ptr, amount);
        //  Search for this address in GLOBAL_LIST
        //  If it is there, replace with new values,
        //  else, add new mem-block
        for (element* p = l->first; p; p = p->next) 
        {
            buffer = ((c_mem_entity*)p->content);
            if(buffer->address == alloc_addr)
            {
                buffer->size = amount;
                buffer->file = file;
                buffer->line = line;
                return buffer->address;
            }
        }
    }
    c_mem_entity new_block;
    new_block.address = alloc_addr;
    new_block.size = amount;
    new_block.file = file;
    new_block.line = line;
    list_push_back(l, (void*)&new_block, sizeof(new_block));
    return alloc_addr;
}

void* memory_data_calloc(size_t amount, size_t size, char* file, size_t line, list* l)
{
    void* alloc_addr = calloc(amount, size);
    c_mem_entity block;

    block.address = alloc_addr;
    block.size = amount*size;
    block.file = file;
    block.line = line;
    list_push_back(l, (void*)&block, sizeof(block));
    return alloc_addr;
}

void memory_data_free(void* ptr, char* file, size_t line, list* l){}
