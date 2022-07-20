/**
 * @file c-mem-block.h
 * @author Vasily Davydov
 * @version 0.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "c-mem.h"

/** Strings to print for user after calling C_MEM_PRINT_$ */
static const char * C_MEM_BUFFER_MESSAGE_TYPE[] = {"malloc", "realloc", "calloc",
                                                   "freed",
                                                   "Could not read memory block."};

void block_value(c_mem_entity *block, void *addr, size_t s, char *fl, size_t l,
                 uint8_t allc_t) {
  block->address = addr;
  block->size = s;
  block->file = fl;
  block->line = l;
  block->alloc_type = allc_t;
}

c_mem_entity create_block() {
  c_mem_entity block;
  block_value(&block, C_MEM_BLOCK_ADDR_INIT, C_MEM_BLOCK_SIZE_INIT,
              C_MEM_BLOCK_FILE_INIT, C_MEM_BLOCK_LINE_INIT,
              C_MEM_BLOCK_ALLOC_TYPE_INIT);
  return block;
}

const char *buffer_to_prt(int code) {
  switch (code) {
  case MALLOCATED:
    return C_MEM_BUFFER_MESSAGE_TYPE[MALLOCATED];
  case REALLOACTED:
    return C_MEM_BUFFER_MESSAGE_TYPE[REALLOACTED];
  case CALLOCATED:
    return C_MEM_BUFFER_MESSAGE_TYPE[CALLOCATED];
  case FREED:
    return C_MEM_BUFFER_MESSAGE_TYPE[FREED];
  }
  return C_MEM_BUFFER_MESSAGE_TYPE[4];
}

int c_mem_generate_message(c_mem_entity *block, char *buffer) {
  return snprintf(buffer, C_MEM_BUFFER_INTERNAL_SIZE,
                  //TODO: Change the format for current message
                  "MEM-Type: [%s] At the address: [%p] with size: [%lu] in "
                  "file: [%s] on line: [%lu]",
                  buffer_to_prt(block->alloc_type), block->address, block->size,
                  block->file, block->line);
}

void c_mem_emit_data(list *l, uint8_t flag) {
  char buffer[C_MEM_BUFFER_INTERNAL_SIZE] = {0};
  c_mem_entity *blcok_iter;
  for (element *p = l->first; p; p = p->next) {
    blcok_iter = ((c_mem_entity *)p->content);
    const size_t bufferSize = c_mem_generate_message(blcok_iter, buffer);
    if (bufferSize) {
      switch (flag) {
      case TRUE:
        printf("%.*s\n", (int)bufferSize, buffer);
        break;
      case FALSE:
        if (blcok_iter->alloc_type != FREED) {
          printf("%.*s\n", (int)bufferSize, buffer);
        }
        break;
      default:
        printf("Wrong argument passed in function: %s", __func__);
        break;
      }
    }
  }
}
