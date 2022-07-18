cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)


add_executable(test testing.c ./src/c-mem-block.c ./src/c-mem-dma-func.c ./src/list.c)
target_include_directories(test PRIVATE . ./inc)
