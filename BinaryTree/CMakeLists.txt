cmake_minimum_required(VERSION 3.3)
project(BinaryTreeHMWK)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES bst.c)
add_executable(BinaryTreeHMWK ${SOURCE_FILES})