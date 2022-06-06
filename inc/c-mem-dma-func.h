#include "list.h"
#include "c-mem-defines.h"
#include "c-mem-block.h"
#include <stdio.h>

#ifndef C_MEM_DMA_FUNC_H
#define C_MEM_DMA_FUNC_H

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

#endif /*C_MEM_DMA_FUNC_H*/