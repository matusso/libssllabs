cmake_minimum_required(VERSION 3.2)

if(WIN32)
    set(CMAKE_C_COMPILER "C:/llvm/bin/clang")
    set(CMAKE_CXX_COMPILER "C:/llvm/bin/clang++")
    set(CMAKE_MAKE_PROGRAM "C:/MinGW/bin/make.exe")
endif()

project(ssllabs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INSTALL_PREFIX /usr/local/)

set(ARCHIVE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib CACHE PATH "Install dir for static libraries")
set(LIBRARY_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib CACHE PATH "Install dir for shared libraries")
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "Install dir for headers")

add_subdirectory(include)
add_subdirectory(src)