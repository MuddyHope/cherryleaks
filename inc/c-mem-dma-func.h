#include "list.h"

/** Add data to mem-block entity
 * 
 * @param amount - amount of bytes to be allocated
 * @param file  - name of teh file where allocation is done
 * @param line - line number where allocation is done
 * @param list - gobal list structure where memory data is stored 
 * @return pointer to allocated memory
 */
void* memory_data_malloc(size_t amount, char* file, size_t line, list *l);

/** Reallocate memory in the mem-block entity
 * 
 * 
 * @param ptr   - This is the pointer to a memory block previously allocated with malloc, calloc or realloc to be reallocated. 
 * @param amount - the amount of bytes to be reallocated
 * @param file  - name of teh file where allocation is done
 * @param line - line number where allocation is done
 * @param list - gobal list structure where memory data is stored 
 * @return pointer to reallocated memory 
 */
void* memory_data_realloc(void* ptr, size_t amount, char* file, size_t line, list *l);