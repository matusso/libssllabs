set(SOURCE_FILES ssllabs.cpp getInfo.cpp analyze.cpp endpoint.cpp)

# linked libraries
set(LIBS ${LIBS} curl)

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
add_definitions(-coverage)
endif()

# shared library
add_library(ssllabs-shared SHARED ${SOURCE_FILES})
set_target_properties(ssllabs-shared PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(ssllabs-shared ${LIBS})
if (WIN32)
    message(STATUS "Installing Windows library")
    install(
            TARGETS ssllabs-shared
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            COMPONENT library
    )
else()
    message(STATUS "Installing Unix shared-library")
    install(TARGETS ssllabs-shared LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/ssllabs)
endif()


# static library
add_library(ssllabs-static STATIC ${SOURCE_FILES})
set_target_properties(ssllabs-static PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(ssllabs-static ${LIBS})
if (WIN32)
    message(STATUS "Installing Windows library")
    install(TARGETS ssllabs-static ARCHIVE DESTINATION ssllabs)
else()
    message(STATUS "Installing Unix static-library")
    install(TARGETS ssllabs-static ARCHIVE DESTINATION ${ARCHIVE_INSTALL_DIR}/ssllabs)
endif()