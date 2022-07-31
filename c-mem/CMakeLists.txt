cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)


add_library(c-mem SHARED c-mem-dma-func.c c-mem-block.c list.c c-mem-entity-d-array.c)

#install(TARGETS c-mem DESTINATION lib)
#install(FILES c-mem DESTINATION include)