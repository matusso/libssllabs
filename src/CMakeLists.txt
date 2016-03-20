cmake_minimum_required(VERSION 3.4)
project(ssllabs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ssllabs.cpp)
set(INSTALL_FOLDER /usr/local/lib/ssllabs)

# linked libraries
set(LIBS ${LIBS} curl)

# shared library
add_library(ssllabs-shared SHARED ${SOURCE_FILES})
set_target_properties(ssllabs-shared PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(ssllabs-shared ${LIBS})
install(TARGETS ssllabs-shared LIBRARY DESTINATION ${INSTALL_FOLDER})

# static library
add_library(ssllabs-static STATIC ${SOURCE_FILES})
set_target_properties(ssllabs-static PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(ssllabs-static ${LIBS})
install(TARGETS ssllabs-static ARCHIVE DESTINATION ${INSTALL_FOLDER})

# install headers
set(HEADERS ssllabs)
install(DIRECTORY ${HEADERS} DESTINATION /usr/local/include)
