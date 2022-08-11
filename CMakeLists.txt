cmake_minimum_required(VERSION 3.16)
project(c-memory)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(cherry_leaks)

add_subdirectory(googletest)

add_executable(hello-world testing.c)

target_link_libraries(hello-world PUBLIC cherry_leaks ${CMAKE_DL_LIBS})

target_include_directories(hello-world PRIVATE cherry_leaks)


add_subdirectory(test)
