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
#include "../cherry_leaks/cherry_leaks.h"
}
/** MEMORY_DATA_MALLOC */
TEST(cMemDmaTest, test_malloc_struct_internal) {

}

TEST(cMemDmaTest, test_malloc_return) {

}

/** MEMORY_DATA_REALLOC */
TEST(cMemDmaTest, test_realloc_struct_internal) {

}

TEST(cMemDmaTest, test_realloc_return) {

}


/** MEMORY_DATA_CALLOC */
TEST(cMemDmaTest, test_calloc_struct_internal) {

}

TEST(cMemDmaTest, test_calloc_return) {

}

/** MEMORY_DATA_FREE */
TEST(cMemDmaTest, test_free_struct_internal) {

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
