//
// Created by VFilms on 20.7.2022.
//
#include <gtest/gtest.h>
extern "C" {
#include "../c-mem/c-mem.h"


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

TEST(c_mem_dma_test, test_free_struct_internal) {
    C_MEM_START
    c_mem_entity *buffer;
    void * pointer = malloc(100);
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