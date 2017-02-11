cmake_minimum_required(VERSION 3.3)
project(CommandLineArgs)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCE_FILES arg_conv.c)
add_executable(CommandLineArgs ${SOURCE_FILES})