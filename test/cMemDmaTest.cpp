/**
 * @file cherry_leaks-dma-test.cpp
 * @author Vasily Davydov
 * @version 0.1
 * @date 2022-07-20
 *
 * @copyright Copyright (c) 2022
 *
 * BASIC TESTS FOR C-MEM-DMA FUNCTIONS
 *
 * These tests are made to test basic functionality
 * inside the dma functions, such as creating the cherry_leaks-block,
 * inserting right values inside the cherry_leaks-entity structure and
 * work according to different parameters.
 *
 */

#include <gtest/gtest.h>
extern "C" {
#include "../cherry_leaks//c-mem.h"
}
/** MEMORY_DATA_MALLOC */
TEST(cMemDmaTest, test_malloc_struct_internal) {
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

TEST(cMemDmaTest, test_malloc_return) {
    C_MEM_START
     c_mem_entity *buffer;
    void *pointer = malloc(100);
    buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
    ASSERT_EQ(pointer, buffer->address);
    list_clear(GLOBAL_LIST);
    free(pointer);
}

/** MEMORY_DATA_REALLOC */
TEST(cMemDmaTest, test_realloc_struct_internal) {
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

TEST(cMemDmaTest, test_realloc_return) {
    C_MEM_START
    c_mem_entity *buffer;
    void *pointer = realloc(nullptr, 100);
    buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
    ASSERT_EQ(pointer, buffer->address);
    list_clear(GLOBAL_LIST);
    free(pointer);
}


/** MEMORY_DATA_CALLOC */
TEST(cMemDmaTest, test_calloc_struct_internal) {
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

TEST(cMemDmaTest, test_calloc_return) {
    C_MEM_START
    c_mem_entity *buffer;
    void *pointer = calloc(1, 100);
    buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
    ASSERT_EQ(pointer, buffer->address);
    list_clear(GLOBAL_LIST);
    free(pointer);
}

/** MEMORY_DATA_FREE */
TEST(cMemDmaTest, test_free_struct_internal) {
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
