//
// Created by VFilms on 20.7.2022.
//
#include <gtest/gtest.h>
extern "C" {
#include "../c-mem/c-mem.h"


TEST(c_mem_dma_test, test_malloc_struct_internal) {
    C_MEM_START
    c_mem_entity *buffer;
    void *pointer = malloc(100);
    buffer = ((c_mem_entity *)GLOBAL_LIST->first->content);
    EXPECT_EQ(buffer->address, pointer);
    EXPECT_EQ(buffer->alloc_type, MALLOCATED);
    EXPECT_EQ(buffer->size, 100);
    C_MEM_END_PRINT_LEFT //TODO: Make a separate version to delete a list
    free(pointer);
}

TEST(c_mem_dma_test, test_realloc_struct_internal) {
    ASSERT_EQ(0, 0);
}

TEST(c_mem_dma_test, test_calloc_struct_internal) {
    ASSERT_EQ(0, 0);
}

TEST(c_mem_dma_test, test_free) {
    ASSERT_EQ(0, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
}