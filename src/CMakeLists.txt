cmake_minimum_required(VERSION 3.4)
project(ssllabs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

# shared library
add_library(ssllabs-shared SHARED ${SOURCE_FILES})
set_target_properties(ssllabs-shared PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)

# static library
add_library(ssllabs-static STATIC ${SOURCE_FILES})
set_target_properties(ssllabs-static PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
