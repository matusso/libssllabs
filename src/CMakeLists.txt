set(SOURCE_FILES ssllabs.cpp getInfo.cpp analyze.cpp)

# linked libraries
set(LIBS ${LIBS} curl)

# shared library
add_library(ssllabs-shared SHARED ${SOURCE_FILES})
set_target_properties(ssllabs-shared PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(ssllabs-shared ${LIBS})
install(TARGETS ssllabs-shared LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/ssllabs)


# static library
add_library(ssllabs-static STATIC ${SOURCE_FILES})
set_target_properties(ssllabs-static PROPERTIES OUTPUT_NAME ssllabs CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(ssllabs-static ${LIBS})
install(TARGETS ssllabs-static ARCHIVE DESTINATION ${ARCHIVE_INSTALL_DIR}/ssllabs)
