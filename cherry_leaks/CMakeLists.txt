cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)


add_library(c-mem SHARED c-mem.c)

#install(TARGETS cherry_leaks DESTINATION lib)
#install(FILES cherry_leaks DESTINATION include)