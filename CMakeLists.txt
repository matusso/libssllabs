cmake_minimum_required(VERSION 3.4)
project(ssllabs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src)
add_subdirectory(tools/ssltest)