#ifndef C_MEM_DEFINES_H
#define C_MEM_DEFINES_H

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

#endif /*C_MEM_DEFINES_H*/