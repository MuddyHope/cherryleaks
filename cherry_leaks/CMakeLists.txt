cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_CXX_STANDARD 11)


add_library(cherry_leaks SHARED cherry_leaks.c)

#install(TARGETS cherry_leaks DESTINATION lib)
#install(FILES cherry_leaks DESTINATION include)