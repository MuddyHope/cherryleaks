/**
 * @file cherry_leaks.h
 * @author Vasily Davydov
 * @version 0.2
 * @date 2022-06-01
 *
 * @copyright Copyright (c) 2022
 *
 * General C-MEM lib header file
 *
 */
#define _GNU_SOURCE
// TODO: add proper documentation

#ifndef C_MEM_H
#define C_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if  defined(__MACH__) || defined(__linux__)
#include <dlfcn.h>

void *(*system_malloc)(size_t) = NULL;
// TODO: remove attributes when they are used
__attribute__((unused)) void *(*system_realloc)(void *, size_t) = NULL;
__attribute__((unused)) void *(*system_calloc)(size_t) = NULL;
void (*system_free)(void *) = NULL;

/** Generating system malloc
 *
 * @param size - the size of the system allocation
 * @return - pointer to allocation
 * */
void *gen_sys_malloc_osx(size_t);

/* Generating system realloc */
__attribute__((unused)) void
gen_sys_realloc_osx(); // TODO: remove attributes when they are used

/* Generating system calloc */
__attribute__((unused)) void
gen_sys_calloc_osx(); // TODO: remove attributes when they are used

/** Generating system free
 * @param pointer - pointer to be freed
 * */
void gen_sys_free_osx(void *);

/* Calling system malloc */
#define SYS_MALLOC(n) gen_sys_malloc_osx(n)

/* Calling system free */
#define SYS_FREE(p) gen_sys_free_osx(p)

#endif /*__MACH__ || __linux__*/

/** Buffer length reserved for internal message */
#define C_MEM_BUFFER_INTERNAL_SIZE 1500

/** A malloc type of memory inside of cherry_leaks-entity */
#define MALLOCATED 0

/** A realloc type of memory inside of cherry_leaks-entity */
#define REALLOACTED 1

/** A calloc type of memory inside of cherry_leaks-entity */
#define CALLOCATED 2

/** A freed type of memory inside of cherry_leaks-entity */
#define FREED 3

/** An initial value for block address in cherry_leaks-entity structure */
#define C_MEM_BLOCK_ADDR_INIT NULL

/** An initial value for block size in cherry_leaks-entity structure */
#define C_MEM_BLOCK_SIZE_INIT 0

/** An initial value for file in cherry_leaks-entity structure */
#define C_MEM_BLOCK_FILE_INIT NULL

/** An initial value for line in cherry_leaks-entity structure */
#define C_MEM_BLOCK_LINE_INIT 0

/** An initial value for allocation type in cherry_leaks-entity structure */
#define C_MEM_BLOCK_ALLOC_TYPE_INIT 255

/** General structure for storing data of allocations
 *
 * - address is used for storing a value returned by
 *   allocator function. Can be changed inside of those
 *   functions.
 * - size of the allocation is interchangeable as well,
 *   since it is possible to reallocate memory on the same address
 * - file is a char string, where program stores last place address
 *   was used in, same goes for {line}
 * - alloc_type is a value which indicates the type of allocation,
 *   this can be used to store user needed data.
 *
 * */
typedef struct c_mem_entity {
  void *address;
  size_t size;
  char *file;
  size_t line;
  uint8_t alloc_type;

} c_mem_entity;

/** Replace values in current block
 *
 * @param block - entity where data whould be replaced
 * @param addr - addr to be replaced
 * @param s - size to be replaced
 * @param fl - filename to be replaced
 * @param l - line to be replaced
 * @param allc_t - allocation type to be replaced
 */
void block_value(c_mem_entity *block, void *addr, size_t s, char *fl, size_t l,
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
int c_mem_generate_message(c_mem_entity *block, char *buffer);

/** Generate buffer according to type
 *
 * @param code - alloc_type
 * @return char* - buffer
 */
const char *buffer_to_prt(int code);

void c_mem_emit_data(uint8_t flag);

/** Add data to mem-block entity
 *
 * @param amount - amount of bytes to be allocated
 * @param file  - name of the file where allocation is done
 * @param line - line number where allocation is done
 * @return pointer to allocated memory
 */
void *memory_data_malloc(size_t amount, char *file, size_t line);

/** Reallocate memory in the mem-block entity
 *
 *
 * @param ptr   - This is the pointer to a memory block previously allocated
 * with malloc, calloc or realloc to be reallocated.
 * @param amount - the amount of bytes to be reallocated
 * @param file  - name of the file where allocation is done
 * @param line - line number where allocation is done
 * @return pointer to reallocated memory
 */
void *memory_data_realloc(void *ptr, size_t amount, char *file, size_t line);

/** Add data to mem-block entity with calloc
 *
 *
 * @param amount - amount of data-units to be allocated
 * @param size - size of a data-unit
 * @param file  - name of the file where allocation is done
 * @param line - line number where allocation is done
 * @return pointer to allocated memory
 */
void *memory_data_calloc(size_t amount, size_t size, char *file, size_t line);

/** Free mem-block entity
 *
 * @param ptr - pointer to allocated memory
 * @param file  - name of the file where freeing is done
 * @param line - line number where freeing is done
 */
void memory_data_free(void *ptr, char *file, size_t line);

// TODO: Make separate bool file
#define TRUE 1

#define FALSE 0

/** Declaration of the Global List, where all allocated data is stored */
// static list *GLOBAL_LIST = NULL;

/** Initialize the program and start recording */
#define C_MEM_START

typedef struct Rame {
  void *data;
  struct Rame *next;
} Rame;

Rame *grow_first_rame();
/** Assign a new beginning of the rame with cherry allocation
 *
 * @param beginning - Reference to the beginning of the Global Rame
 * @param cherry - The element to be written inside Rame
 * @param cherry_size - Size of the element to be written
 */
void grow_cherry_at_beginning(Rame **beginning, void *cherry,
                              size_t cherry_size);

/** Grow a cherry in the middle of other cherries
 *
 * @param cherry_on_rame - The position of cherry on the rame where
 * to grow another cherry
 * @param cherry - The element to be written inside Rame
 * @param cherry_size - Size of the element to be written
 */
void grow_cherry_after_cherry(Rame *cherry_on_rame, void *cherry,
                              size_t cherry_size);

/** Iterator through rame with a (void) callback
 *
 * @param beginning - Reference to the beginning of the Global Rame
 * @param cherry_callback - a callback with type (void) to be executed on each
 * cherry
 */
void for_each_cherry(Rame *beginning, void (*cherry_callback)(void *));

/**
 *
 * @param beginning - Reference to the beginning of the Global Rame
 * @param cherry_callback - a callback with type (int) to be executed on each
 * cherry. May be a comparison.
 * @return Rame* - The rame which matched the condition of the callback.
 */
Rame *find_rame(Rame **beginning, int (*cherry_callback)(void *));

/** Free a particular cherry
 *
 * @param beginning - Reference to the beginning of the Global Rame
 * @param cherry - The cherry to be freed
 *
 * TODO: return value if not found
 */
void pick_cherry(Rame *beginning, void *cherry);

/** Pick all cherries from all rames (Free everything)
 *
 */
void pick_all_cherries();

/** End recording, print all leftovers */
#define C_MEM_END_PRINT_LEFT                                                   \
  c_mem_emit_data(FALSE);                                                      \
  list_clear(GLOBAL_LIST);

/** End recording, print all memory data */
#define C_MEM_END_PRINT_ALL                                                    \
  c_mem_emit_data(TRUE);                                                       \
  pick_all_cherries();

/** ALLOCATORS REPLACED WITH C_MEM_DMA FUNCTIONS
 *
 *  Replacing memory allocation functions, with cherry_leaks-dma functions
 *  in case the program has been started and Global List is initialized.
 * */

/*
 * In case of mac:
 * https://stackoverflow.com/questions/929893/how-can-i-override-malloc-calloc-free-etc-under-os-x
 * In case of Linux: malloc hooks
 *
 * */

#define malloc(n) memory_data_malloc(n, __FILE__, __LINE__)
#define realloc(ptr, n) memory_data_realloc(ptr, n, __FILE__, __LINE__)
#define calloc(n, size) memory_data_calloc(n, size, __FILE__, __LINE__)
#define free(addr) memory_data_free(addr, __FILE__, __LINE__) free(addr)

#ifdef _cplusplus
}
#endif

#endif /*C_MEM_H*/
