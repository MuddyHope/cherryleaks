cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)

add_executable(c-mem-dma-test c-mem-dma-test.cpp)
target_link_libraries(c-mem-dma-test PUBLIC
        gtest_main
        c-mem)

add_test(
        NAME c-mem-dma-test
        COMMAND c-mem-dma-test
)