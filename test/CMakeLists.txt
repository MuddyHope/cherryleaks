cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)

add_executable(cherry_leaks-dma-test cMemDmaTest.cpp)
target_link_libraries(cherry_leaks-dma-test PUBLIC
        gtest_main
        cherry_leaks ${CMAKE_DL_LIBS})

add_test(
        NAME c-mem-dma-test
        COMMAND c-mem-dma-test
)