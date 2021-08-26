cmake_minimum_required(VERSION 3.2)

project(ssllabs)
set(PROJECT_NAME ssllabs)
set(PROJECT_VERSION 1.0)
set(CMAKE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    include_directories(C:/library/curl/include)
    link_directories(C:/library/curl/lib/Debug)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/local/include")
    link_directories(/usr/local/lib)
endif()

set(CMAKE_INSTALL_PREFIX /usr/local/)

set(ARCHIVE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib CACHE PATH "Install dir for static libraries")
set(LIBRARY_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib CACHE PATH "Install dir for shared libraries")
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include CACHE PATH "Install dir for headers")

add_subdirectory(include)
add_subdirectory(src)
