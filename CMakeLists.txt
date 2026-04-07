cmake_minimum_required(VERSION 3.21)

project(ssllabs VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

option(SSLLABS_BUILD_TESTS "Build ssllabs unit tests" ${PROJECT_IS_TOP_LEVEL})
option(SSLLABS_BUILD_TOOLS "Build the ssllabs sample CLI" ${PROJECT_IS_TOP_LEVEL})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/include/rapidjson/include/rapidjson/document.h")
    message(FATAL_ERROR "RapidJSON headers are missing. Run `git submodule update --init --recursive` first.")
endif()

find_package(CURL REQUIRED)

add_subdirectory(src)

if(SSLLABS_BUILD_TOOLS)
    add_subdirectory(tools/ssllabs)
endif()

if(SSLLABS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/ssllabs"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
