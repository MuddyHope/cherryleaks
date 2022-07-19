#include "c-mem.h"

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

char *buffer_to_prt(int code) {
  switch (code) {
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

int c_mem_generate_message(c_mem_entity *block, char *buffer) {
  return snprintf(buffer, BUFFER_INTERNAL_SIZE,
                  "MEM-Type: [%s] At the address: [%p] with size: [%lu] in "
                  "file: [%s] on line: [%lu]",
                  buffer_to_prt(block->alloc_type), block->address, block->size,
                  block->file, block->line);
}

void c_mem_emit_data(list *l, uint8_t flag) {
  char buffer[BUFFER_INTERNAL_SIZE] = {0};
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
        printf("Wrong argument passed in fucntion: %s", __func__);
        break;
      }
    }
  }
}
