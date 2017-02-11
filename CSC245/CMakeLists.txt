cmake_minimum_required(VERSION 3.3)
project(CSC245FinalHmwk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES CFinalHmwk.cpp RGBColor.cpp RGBColor.h)
add_executable(CSC245FinalHmwk ${SOURCE_FILES})