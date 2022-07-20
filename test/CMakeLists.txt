cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)

set(Sources c-mem-dma-test.cpp)

add_executable(tests ${Sources})
target_link_libraries(tests PUBLIC
        gtest_main
        c-mem)

add_test(
        NAME tests
        COMMAND tests
)