add_executable(ssllabs-cli ssllabs.cpp)
set_target_properties(ssllabs-cli PROPERTIES OUTPUT_NAME ssllabs)

target_link_libraries(ssllabs-cli PRIVATE ssllabs::shared)

install(TARGETS ssllabs-cli
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
