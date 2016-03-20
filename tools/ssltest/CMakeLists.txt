cmake_minimum_required(VERSION 3.4)
project(ssltest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

add_executable(ssltest ${SOURCE_FILES})
add_library(ssllabs STATIC IMPORTED)
set_target_properties(ssllabs PROPERTIES IMPORTED_LOCATION ../lib/libssllabs.a)
target_link_libraries(ssltest ssllabs)



