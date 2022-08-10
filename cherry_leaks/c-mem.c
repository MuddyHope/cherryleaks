/**
 * @file cherry_leaks.c
 * @author Vasily Davydov
 * @brief
 * @version 0.2
 * @date 2022-08-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "c-mem.h"

Rame *global = NULL;

#ifdef __MACH__
/*
 * Using RTLD_NEXT to avoid dlopen() calls in system
 * allocation functions.
 */
void *gen_sys_malloc_osx(size_t n) {
  system_malloc = dlsym(RTLD_NEXT, "malloc");
  assert(system_malloc);
  return system_malloc(n);
}

__attribute__((unused)) void gen_sys_realloc_osx() {
  // TODO
}

__attribute__((unused)) void gen_sys_calloc_osx() {
  // TODO
}
void gen_sys_free_osx(void *pointer) {
  system_free = dlsym(RTLD_NEXT, "free");
  assert(system_free);
  system_free(pointer);
}
#endif

void *memory_data_malloc(size_t amount, char *file, size_t line) {
  void *alloc_addr = NULL;
  alloc_addr = SYS_MALLOC(amount);
  assert(alloc_addr);
  c_mem_entity block = create_block();
  block_value(&block, alloc_addr, amount, file, line, MALLOCATED);
  grow_cherry_at_beginning(&global, (void *)&block, sizeof(block));
  return alloc_addr;
}

/* Still needs to be implemented
void *memory_data_realloc(void *ptr, size_t amount, char *file, size_t line) {
  void *alloc_addr;
  c_mem_entity *buffer;

  alloc_addr = realloc(ptr, amount);
  //  Search for this address in GLOBAL_LIST
  //  If it is there, replace with new values,
  //  else, add new mem-block
  for (element *p = l->first; p; p = p->next) {
    buffer = ((c_mem_entity *)p->content);
    if (buffer->address == ptr) {
      block_value(buffer, alloc_addr, amount, file, line, REALLOACTED);
      return alloc_addr;
    }
  }

  c_mem_entity new_block = create_block();
  block_value(&new_block, alloc_addr, amount, file, line, REALLOACTED);
  list_push_back(l, (void *)&new_block, sizeof(new_block));
  return alloc_addr;
}

void *memory_data_calloc(size_t amount, size_t size, char *file, size_t line) {
  void *alloc_addr = calloc(amount, size);
  c_mem_entity block = create_block();
  block_value(&block, alloc_addr, amount, file, line, CALLOCATED);
  list_push_back(l, (void *)&block, sizeof(block));
  return alloc_addr;
}
*/
void memory_data_free(void *ptr, char *file, size_t line) {
  c_mem_entity *buffer;
  Rame *temp = global;
  assert(temp);
  for (temp; temp; temp = temp->next) {
    buffer = ((c_mem_entity *)temp->data);
    if (buffer->address == ptr && buffer->alloc_type != FREED) {
      block_value(buffer, ptr, C_MEM_BLOCK_SIZE_INIT, file, line, FREED);
      SYS_FREE(ptr);
      break;
    }
  }
}

/** Strings to print for user after calling C_MEM_PRINT_$ */
static const char *C_MEM_BUFFER_MESSAGE_TYPE[] = {
    "malloc", "realloc", "calloc", "freed", "Could not read memory block."};

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
  default:
    return C_MEM_BUFFER_MESSAGE_TYPE[4];
  }
}

int c_mem_generate_message(c_mem_entity *block, char *buffer) {
  return snprintf(buffer, C_MEM_BUFFER_INTERNAL_SIZE,
                  // TODO: Change the format for current message
                  "MEM-Type: [%s] At the address: [%p] with size: [%lu] in "
                  "file: [%s] on line: [%lu]",
                  buffer_to_prt(block->alloc_type), block->address, block->size,
                  block->file, block->line);
}

void c_mem_emit_data(uint8_t flag) {
  char buffer[C_MEM_BUFFER_INTERNAL_SIZE] = {0};
  c_mem_entity *block_iter;
  Rame *temp = global;
  for (temp; temp; temp = temp->next) {
    block_iter = ((c_mem_entity *)temp->data);
    const size_t bufferSize = c_mem_generate_message(block_iter, buffer);
    if (bufferSize) {
      switch (flag) {
      case TRUE:
        printf("%.*s\n", (int)bufferSize, buffer);
        break;
      case FALSE:
        if (block_iter->alloc_type != FREED) {
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

static Rame *make_rame() { return (Rame *)SYS_MALLOC(sizeof(Rame)); }

static void *make_cherry(size_t _cherry_size) {
  return SYS_MALLOC(_cherry_size);
}

Rame *grow_first_rame() {
  Rame *initial;
  initial->next = NULL;
  initial->data = NULL;
  return initial;
}

void grow_cherry_at_beginning(Rame **beginning, void *cherry,
                              size_t cherry_size) {

  Rame *new = make_rame();

  void *_cherry_loc = make_cherry(cherry_size);
  memcpy(_cherry_loc, cherry, cherry_size);

  new->data = _cherry_loc;
  new->next = (*beginning);
  (*beginning) = new;
}

void grow_cherry_after_cherry(Rame *cherry_on_rame, void *cherry,
                              size_t cherry_size) {
  /* Assertion of the rame being initialized or not. */
  assert(cherry_on_rame);

  Rame *new = make_rame();

  void *_cherry_loc = make_cherry(cherry_size);
  memcpy(_cherry_loc, cherry, cherry_size);

  new->data = _cherry_loc;
  new->next = cherry_on_rame->next;
  cherry_on_rame->next = new;
}

void for_each_cherry(Rame *beginning, void (*cherry_callback)(void *)) {
  /* Assertion of the rame being initialized or not. */
  assert(beginning);

  for (Rame *temp = beginning; temp; temp = temp->next) {
    cherry_callback(temp->data);
  }
}

Rame *find_rame(Rame **beginning, int (*cherry_callback)(void *)) {
  /* Assertion of the rame being initialized or not. */
  assert(*beginning);

  for (Rame *temp = (*beginning); temp; temp = temp->next) {
    if (cherry_callback(temp->data)) {
      return temp;
    }
  }
  return NULL;
}

void pick_cherry(Rame *beginning, void *cherry) {
  Rame *temp;
  Rame *prev;
  for (temp = beginning; temp; temp = temp->next) {
    if (temp->data == cherry) {
      prev->next = temp->next;
      SYS_FREE(temp->data);
      SYS_FREE(temp);
      return;
    }
    prev = temp;
  }
}

void pick_all_cherries() {
  /* Assertion of the rame being initialized or not. */
  assert(global);
  if (system_free == NULL) {
    system_free = dlsym(RTLD_NEXT, "free");
  }
  /* Free all cherries from rames */
  for_each_cherry(global, system_free);

  /* Free all rames */
  Rame *current = global;
  Rame *next;
  while (current) {
    next = current->next;
    SYS_FREE(current);
    current = next;
  }
  global = NULL;
}
