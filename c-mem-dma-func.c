#include "c-mem.h"


void* memory_data_malloc(size_t amount, char* file, size_t line, list *l)
{
    void* alloc_addr = malloc(amount);
    c_mem_entity block = create_block();
    block_value(&block, alloc_addr, amount, file, line, MALLOCATED);
    list_push_back(l, (void*)&block, sizeof(block));
    return alloc_addr;
}

void* memory_data_realloc(void* ptr, size_t amount, char* file, size_t line, list *l)
{
    void* alloc_addr;
    c_mem_entity* buffer;

    alloc_addr = realloc(ptr, amount);
    //  Search for this address in GLOBAL_LIST
    //  If it is there, replace with new values,
    //  else, add new mem-block
    for (element* p = l->first; p; p = p->next) 
    {
        buffer = ((c_mem_entity*)p->content);
        if(buffer->address == ptr)
        {
            block_value(buffer,
                        alloc_addr,
                        amount,
                        file,
                        line,
                        REALLOACTED);
            return alloc_addr;
        }
    }
    
    c_mem_entity new_block = create_block();
    block_value(&new_block, alloc_addr, amount, file, line, REALLOACTED);
    list_push_back(l, (void*)&new_block, sizeof(new_block));
    return alloc_addr;
}

void* memory_data_calloc(size_t amount, size_t size, char* file, size_t line, list* l)
{
    void* alloc_addr = calloc(amount, size);
    c_mem_entity block = create_block();
    block_value(&block, alloc_addr, amount, file, line, CALLOCATED);
    list_push_back(l, (void*)&block, sizeof(block));
    return alloc_addr;
}

void memory_data_free(void* ptr, char* file, size_t line, list* l)
{
    c_mem_entity* buffer;
    for (element* p = l->first; p; p = p->next) 
        {
            buffer = ((c_mem_entity*)p->content);
            if(buffer->address == ptr && buffer->alloc_type != FREED)
            {
                block_value(buffer,
                            ptr,
                            C_MEM_BLOCK_SIZE_INIT,
                            file,
                            line,
                            FREED);
                free(ptr);
                break;
            }
            // TODO: Add empty list error
        }
}

