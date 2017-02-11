cmake_minimum_required(VERSION 3.3)
project(parent_child_concurrent)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
set(SOURCE_FILES main.c)
add_executable(parent_child_concurrent ${SOURCE_FILES})