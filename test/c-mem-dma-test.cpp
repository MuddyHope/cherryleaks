/**
 * @file c-mem-dma-test.cpp
 * @author Vasily Davydov
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 * BASIC TESTS FOR C-MEM-DMA FUNCTIONS
 *
 * These tests are made to test basic functionality
 * inside the dma functions, such as creating the c-mem-block,
 * inserting right values inside the c-mem-entity structure and
 * work according to different parameters.
 *
 */

#include <gtest/gtest.h>
extern "C" {
#include "../c-mem/c-mem.h"

/** MEMORY_DATA_MALLOC */
TEST(c_mem_dma_test, test_malloc_struct_internal) {
  C_MEM_START
    c_mem_entity *buffer;
  void *pointer = malloc(100); int line = __LINE__;
  buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
  EXPECT_EQ(buffer->address, pointer);
  EXPECT_EQ(buffer->alloc_type, MALLOCATED);
  EXPECT_EQ(buffer->size, 100);
  EXPECT_EQ(buffer->line, line);
  EXPECT_EQ(buffer->file, __FILE__);
  list_clear(GLOBAL_LIST);
  free(pointer);
}

/** MEMORY_DATA_REALLOC */
TEST(c_mem_dma_test, test_realloc_struct_internal) {
  C_MEM_START
    c_mem_entity *buffer;
  void *pointer = realloc(NULL, 100); int line = __LINE__;
  buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
  EXPECT_EQ(buffer->address, pointer);
  EXPECT_EQ(buffer->alloc_type, REALLOACTED);
  EXPECT_EQ(buffer->size, 100);
  EXPECT_EQ(buffer->line, line);
  EXPECT_EQ(buffer->file, __FILE__);
  list_clear(GLOBAL_LIST);
  free(pointer);
}

/** MEMORY_DATA_CALLOC */
TEST(c_mem_dma_test, test_calloc_struct_internal) {
  C_MEM_START
    c_mem_entity *buffer;
  void *pointer = calloc(100, 1); int line = __LINE__;
  buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
  EXPECT_EQ(buffer->address, pointer);
  EXPECT_EQ(buffer->alloc_type, CALLOCATED);
  EXPECT_EQ(buffer->size, 100);
  EXPECT_EQ(buffer->line, line);
  EXPECT_EQ(buffer->file, __FILE__);
  list_clear(GLOBAL_LIST);
  free(pointer);
}

/** MEMORY_DATA_FREE */
TEST(c_mem_dma_test, test_free_struct_internal) {
  C_MEM_START
    c_mem_entity *buffer;
  void *pointer = malloc(100);
  free(pointer); int line = __LINE__;
  buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
  EXPECT_EQ(buffer->address, pointer);
  EXPECT_EQ(buffer->alloc_type, FREED);
  EXPECT_EQ(buffer->size, 0);
  EXPECT_EQ(buffer->line, line);
  EXPECT_EQ(buffer->file, __FILE__);
  list_clear(GLOBAL_LIST);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
}